// Copyright 2023 Noah Beidelman (@noahbei)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "printedpad.h"
#include <stdio.h>
/* oled显示屏部分， oled分辨率32*128px，旋转270° */
/* 图案常量 */
// layer 0 - 5 , 32*22 px
static const char PROGMEM oled_layer_z[] = {0xfc, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xb7, 0xbb, 0xb7, 0x0f, 0xff, 0xf3, 0xef, 0x1f, 
0xef, 0xf3, 0xff, 0x03, 0xdb, 0xdb, 0xdb, 0xfb, 0xff, 0x03, 0xfb, 0x9b, 0x5b, 0xe7, 0xfe, 0xfc, 
0xff, 0x0f, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x07, 0xc7, 0x27, 0x16, 
0x17, 0x27, 0xc7, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x0f, 0xff, 
0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23, 0x24, 0x28, 
0x28, 0x24, 0x23, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x0f};

static const char PROGMEM oled_layer_i[] = {0xfc, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xb7, 0xbb, 0xb7, 0x0f, 0xff, 0xf3, 0xef, 0x1f, 
0xef, 0xf3, 0xff, 0x03, 0xdb, 0xdb, 0xdb, 0xfb, 0xff, 0x03, 0xfb, 0x9b, 0x5b, 0xe7, 0xfe, 0xfc, 
0xff, 0x0f, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x07, 0x07, 0x47, 0x26, 
0xf7, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x0f, 0xff, 
0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 
0x2f, 0x28, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x0f};

static const char PROGMEM oled_layer_ii[] = {0xfc, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xb7, 0xbb, 0xb7, 0x0f, 0xff, 0xf3, 0xef, 0x1f, 
0xef, 0xf3, 0xff, 0x03, 0xdb, 0xdb, 0xdb, 0xfb, 0xff, 0x03, 0xfb, 0x9b, 0x5b, 0xe7, 0xfe, 0xfc, 
0xff, 0x0f, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x07, 0x47, 0x27, 0x16, 
0x17, 0x27, 0xc7, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x0f, 0xff, 
0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2c, 0x2a, 0x29, 
0x29, 0x29, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x0f};

static const char PROGMEM oled_layer_iii[] = {0xfc, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xb7, 0xbb, 0xb7, 0x0f, 0xff, 0xf3, 0xef, 0x1f, 
0xef, 0xf3, 0xff, 0x03, 0xdb, 0xdb, 0xdb, 0xfb, 0xff, 0x03, 0xfb, 0x9b, 0x5b, 0xe7, 0xfe, 0xfc, 
0xff, 0x0f, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x07, 0x27, 0x17, 0x96, 
0x97, 0x57, 0x27, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x0f, 0xff, 
0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x22, 0x24, 0x28, 
0x28, 0x25, 0x22, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x0f};

static const char PROGMEM oled_layer_iv[] = {0xfc, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xb7, 0xbb, 0xb7, 0x0f, 0xff, 0xf3, 0xef, 0x1f, 
0xef, 0xf3, 0xff, 0x03, 0xdb, 0xdb, 0xdb, 0xfb, 0xff, 0x03, 0xfb, 0x9b, 0x5b, 0xe7, 0xfe, 0xfc, 
0xff, 0x0f, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x07, 0x07, 0xc7, 0x26, 
0x17, 0xf7, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x0f, 0xff, 
0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x23, 0x22, 0x22, 
0x22, 0x2f, 0x22, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x0f};

static const char PROGMEM oled_layer_v[] = {0xfc, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xb7, 0xbb, 0xb7, 0x0f, 0xff, 0xf3, 0xef, 0x1f, 
0xef, 0xf3, 0xff, 0x03, 0xdb, 0xdb, 0xdb, 0xfb, 0xff, 0x03, 0xfb, 0x9b, 0x5b, 0xe7, 0xfe, 0xfc, 
0xff, 0x0f, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x07, 0xf7, 0x97, 0x96, 
0x97, 0x17, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x0f, 0xff, 
0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x24, 0x28, 0x28, 
0x28, 0x27, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x0f};

static const char PROGMEM oled_layer_undefined[] = {0xfc, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xb7, 0xbb, 0xb7, 0x0f, 0xff, 0xf3, 0xef, 0x1f, 
0xef, 0xf3, 0xff, 0x03, 0xdb, 0xdb, 0xdb, 0xfb, 0xff, 0x03, 0xfb, 0x9b, 0x5b, 0xe7, 0xfe, 0xfc, 
0xff, 0x0f, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0xc7, 0x27, 0x17, 0x16, 
0x97, 0x57, 0x27, 0xd6, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x07, 0x07, 0x07, 0x06, 0x0f, 0xff, 
0x0f, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x24, 0x2a, 0x29, 
0x28, 0x28, 0x24, 0x23, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x0f};

//  capslock & scrolllock , 32*14 px
static const char PROGMEM oled_capslock_off[] = {0xfc, 0x02, 0x01, 0xe1, 0x11, 0x09, 0x09, 0x11, 0x01, 0x01, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x09, 0x11, 0x21, 0x41, 0x81, 0x21, 0x11, 0x09, 0x01, 0x02, 0xfc, 
0x0f, 0x10, 0x20, 0x21, 0x22, 0x24, 0x24, 0x22, 0x20, 0x20, 0x27, 0x24, 0x24, 0x24, 0x24, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x24, 0x22, 0x21, 0x20, 0x20, 0x21, 0x22, 0x24, 0x20, 0x10, 0x0f};

static const char PROGMEM oled_capslock_on[] = {0xfc, 0xfe, 0xff, 0x1f, 0xef, 0xf7, 0xf7, 0xef, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0xdf, 0xef, 0xff, 0xfe, 0xfc, 
0x0f, 0x1f, 0x3f, 0x3e, 0x3d, 0x3b, 0x3b, 0x3d, 0x3f, 0x3f, 0x38, 0x3b, 0x3b, 0x3b, 0x3b, 0x3f, 
0x3f, 0x3f, 0x3f, 0x3f, 0x3e, 0x3d, 0x3b, 0x3d, 0x3e, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x0f};

static const char PROGMEM oled_scrolllock_off[] = {0xfc, 0x02, 0x01, 0x31, 0x49, 0x49, 0x89, 0x11, 0x01, 0x01, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x01, 0x01, 0x09, 0x11, 0x21, 0x41, 0x81, 0x21, 0x11, 0x09, 0x01, 0x02, 0xfc, 
0x0f, 0x10, 0x20, 0x22, 0x24, 0x24, 0x24, 0x23, 0x20, 0x20, 0x27, 0x24, 0x24, 0x24, 0x24, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x24, 0x22, 0x21, 0x20, 0x20, 0x21, 0x22, 0x24, 0x20, 0x10, 0x0f};

static const char PROGMEM oled_scrolllock_on[] = {0xfc, 0xfe, 0xff, 0xcf, 0xb7, 0xb7, 0x77, 0xef, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0xdf, 0xef, 0xff, 0xfe, 0xfc, 
0x0f, 0x1f, 0x3f, 0x3d, 0x3b, 0x3b, 0x3b, 0x3c, 0x3f, 0x3f, 0x38, 0x3b, 0x3b, 0x3b, 0x3b, 0x3f, 
0x3f, 0x3f, 0x3f, 0x3f, 0x3e, 0x3d, 0x3b, 0x3d, 0x3e, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x0f};

//  wpm , 32*26 px
static const char PROGMEM oled_wpm[] = {0xfc, 0x7e, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0x8f, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x8f, 0xff, 0x0f, 
0x6f, 0x6f, 0x6f, 0x9f, 0xff, 0x0f, 0xef, 0x9f, 0x7f, 0x9f, 0xef, 0x0f, 0xff, 0xff, 0xf6, 0xfc, 
0xff, 0x7f, 0x3e, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3e, 0x39, 0x3e, 0x39, 0x3e, 0x3f, 0x3f, 0x38, 
0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x38, 0x3f, 0x3f, 0x3e, 0x3f, 0x3f, 0x38, 0x3f, 0x3f, 0x77, 0xff, 
0xff, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x08, 0x00, 0xff, 
0x00, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00};

//  logo , 32*40 px
static const char PROGMEM oled_logo[] = {0x00, 0x00, 0x02, 0x07, 0x82, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
0x00, 0x00, 0x20, 0x70, 0x20, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1e, 0x21, 0x40, 0x82, 0x07, 0x02, 0x00, 0x00, 0x89, 0x02, 0x04, 0x08, 0x10, 0x20, 
0x40, 0x90, 0x38, 0x7c, 0xfe, 0xff, 0xef, 0xff, 0x7f, 0xff, 0xfb, 0x71, 0x3b, 0x1e, 0x00, 0x00, 
0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x81, 0xc2, 0xe4, 0xc8, 0x90, 0x20, 0x48, 0x9c, 0x3e, 0x7f, 
0xfe, 0x7c, 0x39, 0x12, 0x04, 0x89, 0x13, 0x27, 0x43, 0x81, 0x00, 0x00, 0x00, 0x10, 0x38, 0x10, 
0x00, 0x00, 0x78, 0xdc, 0x8e, 0xdf, 0xff, 0xff, 0xbf, 0xfd, 0xff, 0x7f, 0x3e, 0x1c, 0x09, 0x02, 
0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x04, 0x00, 0x40, 0xe0, 0x41, 0x02, 0x84, 0x78, 0x00, 0x00, 
0x40, 0xe0, 0x40, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x21, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x10, 0x00, 0x00};



// Layer 状态显示
void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_raw_P(oled_layer_z, sizeof(oled_layer_z));
            break;
        case 1:
            oled_write_raw_P(oled_layer_i, sizeof(oled_layer_i));
            break;
        case 2:
            oled_write_raw_P(oled_layer_ii, sizeof(oled_layer_ii));
            break;
        case 3:
            oled_write_raw_P(oled_layer_iii, sizeof(oled_layer_iii));
            break;
        case 4:
            oled_write_raw_P(oled_layer_iv, sizeof(oled_layer_iv));
            break;
        case 5:
            oled_write_raw_P(oled_layer_v, sizeof(oled_layer_v));
            break;
        default:
            oled_write_raw_P(oled_layer_undefined, sizeof(oled_layer_undefined));
    }
}

// caps scroll 锁定检测
void render_lock_state(void) {
    led_t led_state = host_keyboard_led_state();
    oled_write_raw_P(led_state.caps_lock ? oled_capslock_on : oled_capslock_off, sizeof(oled_capslock_off));
    oled_set_cursor(0,5);
    oled_write_raw_P(led_state.scroll_lock ? oled_scrolllock_on : oled_scrolllock_off, sizeof(oled_scrolllock_off));
}


//	屏幕旋转270°
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_90; }

//	wpm加载
void render_wpm(void) {
    static char wpm_str[6];
   sprintf(wpm_str, "%03d", get_current_wpm());
    // sprintf(wpm_str, "%03d", 0);
    oled_write_P(PSTR(wpm_str), false);
}


/* oled */
bool oled_task_user(void) {
    static uint8_t tick=0;
    tick++;
    tick&=1;
    if(tick==0) {
        oled_set_cursor(0,7);
        oled_write_raw_P(oled_wpm, sizeof(oled_wpm));
        oled_set_cursor(1,9);
        render_wpm();
    } else {
        oled_set_cursor(0,0);
        render_layer_state();
        oled_set_cursor(0,3);
        render_lock_state();
        oled_set_cursor(0,11);
        oled_write_raw_P(oled_logo, sizeof(oled_logo));
        
    }
    return false;
}
