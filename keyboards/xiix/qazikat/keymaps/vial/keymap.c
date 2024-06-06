/* Copyright 2021 weteor
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers
{
    _ALPHA_QWERTY = 0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    
    [_ALPHA_QWERTY] = LAYOUT_12x4(
        KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,   _______, _______,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,
        KC_A,       KC_S,       KC_D,       KC_F,       KC_G,   _______, _______,    KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,
        KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,   _______, _______,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,
        KC_LGUI,    KC_LALT,    _______,    _______,  KC_SPC,   _______, _______,    KC_ENT,     _______,    _______,    KC_RALT,    KC_RGUI
    ),
};

// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0, 3, HSV_RED}     
// );

const rgblight_segment_t PROGMEM _base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, 3, HSV_BLUE}
        );
const rgblight_segment_t PROGMEM _middle_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, 3, HSV_GREEN}
        );
const rgblight_segment_t PROGMEM _top_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, 3, HSV_RED}
        );

const rgblight_segment_t* const PROGMEM _rgb_layers[] =
RGBLIGHT_LAYERS_LIST(
        _base_layer,
        _middle_layer,
        _top_layer
        );

void keyboard_post_init_user(void) {
    rgblight_layers = _rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
        case 0:
            rgblight_blink_layer(0, 500);
            break;
        case 1:
            rgblight_blink_layer(1, 500);
            break;
        case 2:
            rgblight_blink_layer(2, 500);
            break;
    }
    return state;
}