#include "keycode.h"
#include <stdint.h>
#include <stdbool.h>
#include "keymap.h"

/*
 * HHKB Layout
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: Default layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Bspc |
     * |-----------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn |
     * |-----------------------------------------------------------|
     * |    |Gui |Alt |      Space             |    |Alt |Gui |    |
     * `-----------------------------------------------------------'
     */
     {
        {KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7},
        {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U},
        {KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J},
        {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M},
        {KC_NO,   KC_LGUI, KC_LALT, KC_SPC,  KC_NO,   KC_RALT, KC_RGUI, KC_NO},
        {KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  KC_NO},
        {KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_QUOT, KC_ENT},
        {KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_FN0,  KC_K,    KC_L,    KC_SCLN}
     },
    /* KEYMAP_HHKB(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS, GRV, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC,      \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,       \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,FN0,       \
        NO,  LGUI,LALT,          SPC,                     NO,  RALT,RGUI,NO), */
    /* 1: HHKB Fn layer
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |     |
     * |-----------------------------------------------------------|
     * |      |VoD|VoU|Mut|Ejc|   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |  +|  -|End|PgD|Dow|      |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     */
    {
        {KC_PWR,  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_F7},
        {KC_CAPS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS},
        {KC_TRNS, KC_VOLD, KC_VOLU,  KC_MUTE, KC_EJCT, KC_TRNS, KC_PAST,KC_PSLS},
        {KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS,KC_PMNS},
        {KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS},
        {KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_INS,  KC_DEL, KC_NO},
        {KC_PSCR, KC_SLCK, KC_PAUS,  KC_UP,   KC_TRNS, KC_TRNS, KC_QUOT,KC_ENT},
        {KC_END,  KC_PGDN, KC_DOWN,  KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP,KC_LEFT}
    }
    /* KEYMAP_HHKB(
        PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,  \
        CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,UP,  TRNS,TRNS,      \
        TRNS,VOLD,VOLU,MUTE,EJCT,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,     PENT,      \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,     TRNS,TRNS,      \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,TRNS,TRNS,TRNS), */
};

/*
 * Fn action definition
 */
const action_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
};
