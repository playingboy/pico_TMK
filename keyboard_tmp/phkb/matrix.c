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
#include "timer.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static bool debouncing = false;
static uint16_t debouncing_time = 0;


/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];


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
    palSetPadMode(0,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(1,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(2,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(4,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(5,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(6,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(7,  PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
    
    palSetPadMode(9,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(10,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(11,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(12, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(13, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(14,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(15,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(16,  PAL_MODE_OUTPUT_PUSHPULL);

    memset(matrix, 0, MATRIX_ROWS);
    memset(matrix_debouncing, 0, MATRIX_ROWS);
}

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;

        // strobe row
        switch (row) {
            case 0: gpio_put(9, 1);     break;
            case 1: gpio_put(10, 1);    break;
            case 2: gpio_put(11, 1);    break;
            case 3: gpio_put(12, 1);    break;
            case 4: gpio_put(13, 1);    break;
            case 5: gpio_put(14, 1);    break;
            case 6: gpio_put(15, 1);    break;
            case 7: gpio_put(16, 1);    break;
        }

        busy_wait_us(1); // need wait to settle pin state

        // read col data
        data = gpio_get_all();

        // un-strobe row
        switch (row) {
            case 0: gpio_put(9, 0);     break;
            case 1: gpio_put(10, 0);    break;
            case 2: gpio_put(11, 0);    break;
            case 3: gpio_put(12, 0);    break;
            case 4: gpio_put(13, 0);    break;
            case 5: gpio_put(14, 0);    break;
            case 6: gpio_put(15, 0);    break;
            case 7: gpio_put(16, 0);    break;
        }

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
    xprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: ");
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                xprintf("1");
            else
                xprintf("0");
        }
        xprintf("\n");
    }
}