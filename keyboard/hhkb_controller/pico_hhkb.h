#ifndef PICO_HHKB_H
#define PICO_HHKB_H

#include <hardware/gpio.h>
#include <stdint.h>
#include "pico/time.h"

/*
 * HHKB Matrix I/O
 *
 * row:     HC4051[A,B,C]  selects scan row0-7
 * row-ext: [En0,En1] row extention for JP
 * col:     LS145[A,B,C,D] selects scan col0-7 and enable(D)
 * key:     on: 0/off: 1
 * prev:    hysteresis control: assert(1) when previous key state is on
 */

 /*
 * For PICO HHKB alt controller
 *
 * row:     GPIO2, GPIO3, GPIO6
 * col:     GPIO7, GPIO8, GPIO9, GPIO10
 * key:     GPIO11(pull-uped)
 * prev:    GPIO12
 * power:   GPIO13(L:off/H:on)
 * row-ext: GPIO14, GPIO15 for HHKB JP(active low)
 */
static uint8_t row[3] = {6, 7, 8};
static uint8_t col[3] = {9, 10, 11};
static uint8_t enable = 12;
static uint8_t key = 2;
static uint8_t prev = 3;
static uint8_t power = 13;
static uint8_t row_ext[2] = {14, 15};



static inline void KEY_ENABLE(void) { gpio_pull_down(enable); }
static inline void KEY_UNABLE(void) { gpio_pull_up(enable); }
static inline bool KEY_STATE(void) { return gpio_get(key); }
static inline void KEY_PREV_ON(void) { gpio_pull_up(prev); }
static inline void KEY_PREV_OFF(void) { gpio_pull_down(prev); }
static inline void KEY_POWER_ON(void) {
    gpio_set_dir_out_masked(0x1FC8);
    gpio_pull_up(enable);        // change pins output
    gpio_set_dir(power, 1);
    gpio_pull_up(power);        // MOS FET switch on
    /* Without this wait you will miss or get false key events. */
    sleep_ms(5);               // wait for powering up
}
static inline void KEY_POWER_OFF(void) {
    /* input with pull-up consumes less than without it when pin is open. */
    gpio_set_dir_in_masked(0x1FC8);
    gpio_set_mask(0x1FC8);          // change pins input with pull-up
    gpio_set_dir(power, 1);
    gpio_pull_down(power);   //  MOS FET switch off
}
static inline bool KEY_POWER_STATE(void) { return gpio_get(power); }

static inline void KEY_INIT(void)
{
    /* row,col,prev: output */
    gpio_set_dir_out_masked(0x1FC8);
    gpio_pull_up(enable);   // unable
    /* key: input with pull-up */
    gpio_set_dir(prev, 0);
    gpio_pull_up(prev);
#ifdef HHKB_JP
    /* row extention for HHKB JP */
    gpio_set_dir_out_masked(0xC000);
    gpio_set_mask(0xC000);
#else
    /* input with pull up to save power */
    gpio_set_dir_in_masked(0xC000);
    gpio_set_mask(0xC000);
#endif
    KEY_UNABLE();
    KEY_PREV_OFF();

    KEY_POWER_OFF();
}

static inline void KEY_SELECT(uint8_t ROW, uint8_t COL)
{
    for (uint8_t i = 0; i < 3; i++) {
        if((ROW >> i) & 1) {
            gpio_pull_up(row[i]);
        } else {
            gpio_pull_down(row[i]);
        }
        if((COL >> i) & 1) {
            gpio_pull_up(col[i]);
        } else {
            gpio_pull_down(col[i]);
        }
    }
#ifdef HHKB_JP
    if ((ROW) & 0x08) {
        gpio_pull_up(row_ext[0]);
        gpio_pull_down(row_ext[1]);
    } else {
        gpio_pull_down(row_ext[0]);
        gpio_pull_up(row_ext[1]);
    }
#endif
}

 #endif