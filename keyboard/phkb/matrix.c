/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <hardware/gpio.h>

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"
#include "timer.h"
#include "wait.h"
#include "matrix.h"
#include "stdio.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static bool debouncing = false;
static uint16_t debouncing_time = 0;


/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

uint8_t pin_column[MATRIX_ROWS] = {2, 3, 6,7,8,9,10,11};
uint8_t pin_row[MATRIX_ROWS] = {12, 13, 14, 15,20, 21, 22, 26};

#define PAL_MODE_INPUT_PULLDOWN 1
#define PAL_MODE_OUTPUT_PUSHPULL 2

void palSetPadMode(uint pin, int mod){
    gpio_init(pin);
    if(mod == PAL_MODE_INPUT_PULLDOWN){
        gpio_set_dir(pin, false);
        gpio_pull_down(pin);
    } else if(mod == PAL_MODE_OUTPUT_PUSHPULL){
        gpio_set_dir(pin, true);
        gpio_pull_up(pin);
    }
}

void matrix_init(void)
{
    /* Column(sense) */
    for(int i = 0; i < MATRIX_COLS; i++){
        palSetPadMode(pin_column[i], PAL_MODE_INPUT_PULLDOWN);
    }

    /* Row(strobe) */
    for(int i = 0; i < MATRIX_ROWS; i++) {
        palSetPadMode(pin_row[i], PAL_MODE_OUTPUT_PUSHPULL);
    }

    memset(matrix, 0, MATRIX_ROWS);
    memset(matrix_debouncing, 0, MATRIX_ROWS);
}

matrix_row_t get_data(void){
    uint32_t data = gpio_get_all();
    matrix_row_t re = 0;
    for(int i = 0; i < MATRIX_COLS; i++) {
        re += ((1 & (data >> pin_column[i])) << i);
    }
    return re;
}

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;
        // strobe row
        gpio_put(pin_row[row], true);

        wait_us(1); // need wait to settle pin state

        // read col data
        data = get_data();
        

        // un-strobe row
        gpio_put(pin_row[row], false);

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    printf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("%02X: ");
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}