#ifdef RGB_MATRIX_ENABLE
// LED index
// 9    10    2    3
//         1
//         0
//   8 7   6   5 4

led_config_t g_led_config = {
    // Key Matrix to LED Index
    {
         {9,     9,    9,   9,    9,            3, 3, 3,    3,     3 },
         {10,    10,   10,  10,   10,           2, 2, 2,    2,     2 },
         {8,     8,    8,   8,    8,            4, 4, 4,    4,     4 },
         {NO_LED, NO_LED, 7, NO_LED,      6,    6, 6, 5, NO_LED, NO_LED, }
    },
    // LED Index to Physical Positon
    {
        { 128, 40 },
        { 128, 30 },
        { 166, 0 },
        { 255, 0 },
        { 255, 48 },
        { 178, 64 },
        { 128, 64 },
        { 77, 64 },
        { 0, 48 },
        { 0, 0 },
        { 115, 0 }
    },
    //  LED Index to Flag
    //  https://docs.qmk.fm/#/feature_rgb_matrix?id=flags
    { 8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
};
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 1:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            case 2:
                rgb_matrix_set_color(i, RGB_ORANGE);
                break;
            case 3:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            case 4:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            case 5:
                rgb_matrix_set_color(i, RGB_CYAN);
                break;
            case 6:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case 7:
                rgb_matrix_set_color(i, RGB_PURPLE);
                break;
            default:
                break;
        }
    }
    return false;
}


#endif
