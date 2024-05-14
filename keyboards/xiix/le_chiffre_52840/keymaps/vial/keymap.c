// Copyright 2023 sporkus
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

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
           LT(1, KC_ESC),  KC_SPC, LT(1,KC_SPC),                 LT(2,KC_SPC),KC_SPC, LT(2, KC_BSPC))
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