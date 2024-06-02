// Copyright 2023 sporkus
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "../../rgb.c"

#define HM_A	LSFT_T(KC_A)
#define HM_S	LALT_T(KC_S)
#define HM_D	LGUI_T(KC_D)
#define HM_F	LCTL_T(KC_F)
#define HM_J	RCTL_T(KC_J)
#define HM_K	RGUI_T(KC_K)
#define HM_L	RALT_T(KC_L)
#define HM_Z	LSFT_T(KC_Z)
#define HM_SLSH	LSFT_T(KC_SLSH)
#define HM_QUOT	RSFT_T(KC_QUOT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,      KC_MUTE,     KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,
         HM_A,   HM_S,   HM_D,   HM_F,   KC_G,                   KC_H,   HM_J,   HM_K,    HM_L,   HM_QUOT,
         HM_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_N,   KC_M,   KC_COMM, KC_DOT, HM_SLSH,
                   LT(1, KC_ESC),  LT(1,KC_SPC),                 LT(2,KC_SPC), LT(2, KC_BSPC)
    ),

    [1] = LAYOUT(
         _______,  _______,  _______,  KC_SCLN,  _______,  _______,  KC_EQL,   KC_7,     KC_8,     KC_9,     KC_0,
         _______,  _______,  _______,  KC_COLN,  _______,            KC_MINS,  KC_4,     KC_5,     KC_6,     _______,
         _______,  _______,  _______,  _______,  _______,            KC_BSLS,  KC_1,     KC_2,     KC_3,     _______,
                                       _______,  KC_ENT,             KC_TAB,  _______
    ),

    [2] = LAYOUT(
         _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   KC_BSPC,   _______,    _______,
         _______,  _______,  _______,  _______,  _______,            KC_LEFT,  KC_DOWN,   KC_UP,     KC_LEFT,    _______,
         _______,  _______,  _______,  _______,  _______,            _______,  _______,   _______,   _______,    _______,
                                       _______,  KC_ENT,             KC_TAB,  _______
    )
};

#ifdef ENCODER_MAP_ENABLE
#undef BLANK_LAYER
#define BLANK_LAYER { ENCODER_CCW_CW(_______, _______) }
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   BLANK_LAYER,
    [2] =   BLANK_LAYER
};
#endif

#ifdef OLED_ENABLE
#    define LOGO_SIZE 384
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    static const char PROGMEM ducky_logo[LOGO_SIZE] = {
      // clang-format off
      0, 0, 0, 0,128,128,128,128,128, 0, 0,252,252,252, 0, 0, 0,128,128,128, 0, 0, 0, 0, 0,128,128,128, 0, 0, 0, 0, 0,128,128,128,128,128, 0, 0, 0, 0, 0,252,252,252, 0, 0, 0, 0, 0,128,128,128,128,128,128, 0, 0, 0, 0, 0, 0,128,128,128,128, 0,248,248,248, 56, 56, 56, 56, 56, 56,120,240,224,192, 0, 0,128,128,128,128,128,128, 0, 0, 0, 0, 0, 0, 0, 0,128,128,128,128,128, 0, 0,252,252,252, 0, 0, 0, 0, 0,232, 24, 24,232, 0, 24, 48, 48, 24, 0,232, 24, 24,232, 0, 0,
      0,248,254,255,143, 7, 3, 3, 3, 7,142,255,255,255, 0, 0, 0,255,255,255, 0, 0, 0, 0, 0,255,255,255, 0,248,254,255,143, 7, 3, 3, 3, 3,143, 7, 2, 0, 0,255,255,255,240,120,252,254,231,131, 1, 0, 1, 7, 63,254,240,192, 0,224,252,127, 31, 3, 0, 0,255,255,255,112,112,112,112,112,112, 56, 63, 31, 15,193,231,243,115, 51, 51, 51, 55,255,255,252, 0, 0,248,254,255,143, 7, 3, 3, 3, 7,142,255,255,255, 0, 0, 0, 0, 0, 21,127,127,252,252,252,253,253,252,252,252,255,255,255, 0, 0,
      0, 0, 3, 7, 15, 15, 14, 14, 14, 7, 3, 15, 15, 15, 0, 0, 0, 3, 7, 15, 15, 14, 14, 6, 3, 15, 15, 15, 0, 0, 3, 7, 7, 15, 14, 14, 14, 14, 7, 7, 2, 0, 0, 15, 15, 15, 0, 0, 0, 1, 3, 15, 15, 12,136,224,224,224,247,127,127, 31, 3, 0, 0, 0, 0, 0, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 7, 15, 14, 14, 14, 6, 3, 15, 15, 15, 0, 0, 0, 3, 7, 15, 15, 14, 14, 14, 7, 3, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 7, 11, 3, 11, 7, 11, 7, 7, 31, 0, 0
      //clang-format on
    };
    oled_write_raw_P(ducky_logo, LOGO_SIZE);
    return false;
}
#endif