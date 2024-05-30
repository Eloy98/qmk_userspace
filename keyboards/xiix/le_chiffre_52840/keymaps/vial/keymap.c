#include QMK_KEYBOARD_H
#include "nrf_gpio.h"
#include "eeprom.h"
#include "string.h"
#include "eeconfig.h"
#include "action.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "protocol_mode.h"
#include "rgb_matrix.h"
#include "qf.h"


#define BL_SW_1     KC_F23  // 开启蓝牙通道1（需要打开蓝牙的条件下才行）
#define BL_SW_2     KC_F19  // 开启蓝牙通道2（需要打开蓝牙的条件下才行）
#define BL_SW_3     KC_F20  // BLE3
#define RADIO      KC_F18  // RADIO

#define BLE_DEL     KC_F22  // 删除当前蓝牙绑定
#define BL_DFU     KC_F21  //
#define BAU_TOG     KC_F17  // 蓝牙和USB之间切换
#define MANUAL_SWITCH_MODE     KC_F15  // auto switch close or on
#define ADC_RGB_SHOW     KC_F14  // Show BAT Power
#define LOCK_KB     KC_F24  // KB Lock

extern rgb_config_t rgb_matrix_config;

#define LAYOUT_42(\
	K00, K01, K02, K03,K04,K05,K06,K07,K08,K09, \
	K10, K11, K12, K13, \
	K20, K21, K22, K23, \
	K30, K31, K32,      \
	K40, K41, K42, K43, \
	K50,      K52  \
) { \
	{ K00,   K01,   K02,   ,K04,K05,K06,K07,K08,K09}, \
	{ K10,   K11,   K12,   K13 }, \
	{ K20,   K21,   K22,   K23 }, \
	{ K30,   K31,   K32,   KC_NO }, \
	{ K40,   K41,   K42,   K43 }, \
	{ K50,   KC_NO, K52,   KC_NO }  \
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        { KC_ESC, KC_Q,     KC_W,    KC_E,   KC_R,          KC_T,  KC_Y,   KC_U, KC_I,     KC_O,  KC_P},
        { MO(3),  KC_A,    KC_S,    KC_D,   KC_F,          KC_G,  KC_H,   KC_J, KC_K,     KC_L,  KC_ENTER},
        { KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,          KC_B,  KC_N,   KC_M, KC_COMM,  KC_UP, MO(1)},
        { KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_NO,         KC_NO, KC_SPC, KC_LEFT,KC_DOWN,  KC_RIGHT,KC_BSPC}
    },
    [1] = {
        { QK_BOOT, KC_1,    KC_2,    KC_3,   KC_4,          KC_5,  KC_6,   KC_7, KC_8,     KC_9,     KC_0},
        { KC_TAB,  KC_A,    RGB_MOD,    RGB_TOG,   KC_F,          KC_G,  KC_H,   KC_J, KC_K,     KC_L,     KC_ENTER},
        { KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,          KC_B,  KC_N,   KC_M, KC_DOT,  KC_PGUP,  KC_NO},
        { KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_NO,         KC_NO, KC_SPC,  MO(2),        KC_PGDN,  KC_INS,KC_MINS}
    },
    [2] = {
        { QK_BOOT, BL_SW_1, BL_SW_2,  BL_SW_3, RADIO,      KC_T,  KC_Y,   KC_U, KC_I,     KC_O,     KC_P},
        { KC_TAB,  BLE_DEL, KC_S,    KC_D,   KC_F,          KC_G,  KC_H,   KC_J, KC_K,     KC_L,     KC_ENTER},
        { KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,          BLE_DEL,  KC_N,   KC_M, KC_DOT,     KC_PGUP,  KC_NO},
        { KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_NO,         KC_NO, KC_SPC, KC_NO,  KC_PGDN,  KC_INS,KC_EQL}
    },
    [3] = {
        { QK_BOOT, KC_1,        KC_2,    KC_3,   KC_4,          KC_5,     KC_6,   KC_7, KC_8,       KC_9,     KC_0},
        { KC_TAB,  KC_A,        RGB_MOD, RGB_TOG,KC_F,          KC_G,     KC_H,   KC_J, KC_K,       KC_L,     KC_ENTER},
        { KC_LSFT, KC_Z,        KC_X,    KC_C,   KC_V,          KC_B,     KC_N,   KC_M, KC_DOT,     KC_PGUP,  KC_NO},
        { KC_LCTL, KC_LGUI,     KC_LALT, KC_SPC, KC_NO,         KC_NO,    KC_SPC, KC_NO,            KC_PGDN,  KC_INS,KC_EQL}
    }
};

static bool process_record_user_special(uint16_t keycode, keyrecord_t *record)
{
    bool pressed = record->event.pressed;
    switch (keycode) {
        case BLE_DEL:
            if (pressed) {
                NRF_LOG_INFO("rebond current\n");
                extern void switch_device_rebond(void);
                switch_device_rebond();
            }
            break; 
       case BL_SW_1:
            if (pressed) {
                change_send_mode(MXKBD_BLE_CHANNEL_1);
            }
            break;
        case BL_SW_2:
           if (pressed) {
      
                change_send_mode(MXKBD_BLE_CHANNEL_2);
            }
            break;
        case BL_SW_3:
            if (pressed) {
                change_send_mode(MXKBD_BLE_CHANNEL_3);
            }
            break;
        case RADIO:
            if (pressed) {
                NRF_LOG_INFO("sel radio");
                change_send_mode( MXKBD_GZLL_MODE);//7u is gz, 8u is esb
            }
            break;
        case RGB_TOG:
            if (record->event.pressed) {
                if (rgb_matrix_config.enable) {
                    rgb_matrix_disable();
                    wait_ms(50);
                    rgb_power_enable(false);
                    NRF_LOG_INFO("RGB_TOG, RGB disabled");
                } else {
                    rgb_power_enable(true);
                    rgb_matrix_enable();
                    wait_ms(50);
                    NRF_LOG_INFO("RGB_TOG, RGB enabled");
                }
            }
            return false;
            break;
        default:
            return true;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        static bool caps_state = 0;
        case KC_CAPS:
            if (record->event.pressed) {
                if (caps_state) {
                    caps_state = !caps_state;
                    NRF_LOG_INFO("caps unlocked\n");
                    nrf_gpio_pin_clear(LED_PIN);
                } else {
                    caps_state = !caps_state;
                    nrf_gpio_pin_set(LED_PIN);
                    NRF_LOG_INFO("caps locked\n");
                }
            }
            break;
    }

    switch (keycode) {
        default:
            // unset_layer(record);
            return process_record_user_special(keycode, record);
    }
    return false;
    
}


/**
 * *************************************************************
 * RGB Matrix start
 * *************************************************************
 */
#ifdef RGB_MATRIX_ENABLE
#define XX 255
// clang-format off

led_config_t g_led_config = {
	{
		{0,  1,  2,  3,    4,        5,  6,  7,  8,  9,  10},
		{12, 13, 14, 15,   16,       17, 18, 19, 20, 21, 22},
		{23, 24, 25, 26,   27,       28, 29, 30, 31, 32, 33},
		{34, 35, 36,NO_LED,NO_LED,   37, 38, 39, 40, 41, 11},
	}, {

        {9, 4}, {28, 4}, {47, 4}, {65, 4}, {84, 4}, {103, 4}, {121, 4}, {140, 4}, {159, 4}, {177, 4}, {196, 4}, 
		{215, 4},
		{12, 20}, {33, 20}, {51, 20}, {70, 20}, {89, 20}, {107, 20}, {126, 20}, {145, 20}, {163, 20}, {182, 20}, {208, 20}, 
		{16, 36}, {42, 36}, {61, 36}, {79, 36}, {98, 36}, {117, 36}, {135, 36}, {154, 36}, {173, 36}, {191, 36}, {212, 36}, 
		{12, 52}, {33, 52}, {54, 52}, {86, 52}, {133, 52}, {170, 52}, {191, 52}, {212, 52}, 
	}, {
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
		4, 4, 4,       4, 4, 4, 4, 4, 
	}
};
#endif
