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
    static void render_logo(void) {
        static const char PROGMEM qmk_logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };

        oled_write_P(qmk_logo, false);
    }

    bool oled_task_user(void) {
        render_logo();
        return false;
    }
#endif