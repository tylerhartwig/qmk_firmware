#include "liminas.h"

#include "quantum.h"
#include <math.h>
#include "report.h"


/*
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = ws2812_init,
    .flush         = ws2812_flush,
    .set_color     = ws2812_set_color,
    .set_color_all = ws2812_set_color_all,
};
*/

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    // Key-to-LED matrix mapping
    // Left half (rows 0-4), then right half (rows 5-9)
    {
        // Left half
        {  0,  4,  8, 12, 16, 20 },
        {  1,  5,  9, 13, 17, 21 },
        {  2,  6, 10, 14, 18, 22 },
        {  3,  7, 11, 15, 19, 23 },
        { 24, 25, 26, 27, 28, 29 },
        // Right half
        { 124, 128, 132, 136, 140, 144 },
        { 125, 133, 133, 137, 141, 145 },
        { 126, 130, 134, 138, 142, 146 },
        { 127, 131, 135, 139, 143, 147 },
        { 148, 149, 150, 151, 152, 153 }
    },
    // Physical LED positions (x, y) - range 0-224 for x, 0-64 for y
    {
        // Left half (LEDs 0-23, column order)
        {  0,  0}, {  0, 16}, {  0, 32}, {  0, 48},  // Column 0
        { 20,  0}, { 20, 16}, { 20, 32}, { 20, 48},  // Column 1
        { 40,  0}, { 40, 16}, { 40, 32}, { 40, 48},  // Column 2
        { 60,  0}, { 60, 16}, { 60, 32}, { 60, 48},  // Column 3
        { 80,  0}, { 80, 16}, { 80, 32}, { 80, 48},  // Column 4
        {100,  0}, {100, 16}, {100, 32}, {100, 48},  // Column 5
		// Left Thumb Cluster
        {101, 52}, {108, 54}, {104, 50}, {102, 60}, {111, 58}, {111, 64},
		// Left Underglow
    	{  54,  35 }, // 0
        {  56,  37 }, // 1
        {  58,  39 }, // 2
        {  60,  42 }, // 3
        {  61,  45 }, // 4
        {  62,  48 }, // 5
        {  62,  51 }, // 6
        {  62,  54 }, // 7
        {  60,  56 }, // 8
        {  56,  56 }, // 9
        {  53,  56 }, // 10
        {  50,  57 }, // 11
        {  47,  57 }, // 12
        {  44,  58 }, // 13
        {  41,  59 }, // 14
        {  38,  61 }, // 15
        {  35,  62 }, // 16
        {  32,  63 }, // 17
        {  29,  63 }, // 18
        {  26,  63 }, // 19
        {  23,  62 }, // 20
        {  20,  61 }, // 21
        {  19,  58 }, // 22
        {  17,  55 }, // 23
        {  16,  52 }, // 24
        {  15,  49 }, // 25
        {  13,  47 }, // 26
        {  11,  45 }, // 27
        {   8,  44 }, // 28
        {   5,  43 }, // 29
        {   2,  41 }, // 30
        {   2,  38 }, // 31
        {   2,  35 }, // 32
        {   2,  32 }, // 33
        {   2,  29 }, // 34
        {   2,  26 }, // 35
        {   2,  23 }, // 36
        {   1,  19 }, // 37
        {   1,  16 }, // 38
        {   1,  13 }, // 39
        {   2,  10 }, // 40
        {   5,   9 }, // 41
        {   8,   7 }, // 42
        {  10,   5 }, // 43
        {  13,   4 }, // 44
        {  16,   2 }, // 45
        {  18,   1 }, // 46
        {  21,   0 }, // 47
        {  25,   0 }, // 48
        {  28,   0 }, // 49
        {  31,   0 }, // 50
        {  34,   1 }, // 51
        {  37,   2 }, // 52
        {  40,   3 }, // 53
        {  43,   4 }, // 54
        {  46,   5 }, // 55
        {  47,   7 }, // 56
        {  48,  11 }, // 57
        {  48,  14 }, // 58
        {  48,  17 }, // 59
        {  48,  20 }, // 60
        {  49,  23 }, // 61
        {  50,  26 }, // 62
        {  51,  29 }, // 63
        {  52,  32 }, // 64
		// Left UNDERGLOW, temp copied from underglow
		{  54,  35 }, // 0
        {  56,  37 }, // 1
        {  58,  39 }, // 2
        {  60,  42 }, // 3
        {  61,  45 }, // 4
        {  62,  48 }, // 5
        {  62,  51 }, // 6
        {  62,  54 }, // 7
        {  60,  56 }, // 8
        {  56,  56 }, // 9
        {  53,  56 }, // 10
        {  50,  57 }, // 11
        {  47,  57 }, // 12
        {  44,  58 }, // 13
        {  41,  59 }, // 14
        {  38,  61 }, // 15
        {  35,  62 }, // 16
        {  32,  63 }, // 17
        {  29,  63 }, // 18
        {  26,  63 }, // 19
        {  23,  62 }, // 20
        {  20,  61 }, // 21
        {  19,  58 }, // 22
        {  17,  55 }, // 23
        {  16,  52 }, // 24
        {  15,  49 }, // 25
        {  13,  47 }, // 26
        {  11,  45 }, // 27
        {   8,  44 }, // 28




        // Right half (LEDs 128-151, column order)
        {124,  0}, {124, 16}, {124, 32}, {124, 48},  // Column 0
        {144,  0}, {144, 16}, {144, 32}, {144, 48},  // Column 1
        {164,  0}, {164, 16}, {164, 32}, {164, 48},  // Column 2
        {184,  0}, {184, 16}, {184, 32}, {184, 48},  // Column 3
        {204,  0}, {204, 16}, {204, 32}, {204, 48},  // Column 4
        {224,  0}, {224, 16}, {224, 32}, {224, 48},  // Column 5
		// Right Thumb Cluster
        {123, 52}, {116, 54}, {120, 50}, {122, 60}, {113, 58}, {113, 64},
		// Right Underglow
        { 169,  35 }, // 0
        { 167,  37 }, // 1
        { 165,  39 }, // 2
        { 163,  42 }, // 3
        { 162,  45 }, // 4
        { 161,  48 }, // 5
        { 161,  51 }, // 6
        { 161,  54 }, // 7
        { 163,  56 }, // 8
        { 167,  56 }, // 9
        { 170,  56 }, // 10
        { 173,  57 }, // 11
        { 176,  57 }, // 12
        { 179,  58 }, // 13
        { 182,  59 }, // 14
        { 185,  61 }, // 15
        { 188,  62 }, // 16
        { 191,  63 }, // 17
        { 194,  63 }, // 18
        { 197,  63 }, // 19
        { 200,  62 }, // 20
        { 203,  61 }, // 21
        { 204,  58 }, // 22
        { 206,  55 }, // 23
        { 207,  52 }, // 24
        { 208,  49 }, // 25
        { 210,  47 }, // 26
        { 212,  45 }, // 27
        { 215,  44 }, // 28
        { 218,  43 }, // 29
        { 221,  41 }, // 30
        { 221,  38 }, // 31
        { 221,  35 }, // 32
        { 221,  32 }, // 33
        { 221,  29 }, // 34
        { 221,  26 }, // 35
        { 221,  23 }, // 36
        { 222,  19 }, // 37
        { 222,  16 }, // 38
        { 222,  13 }, // 39
        { 221,  10 }, // 40
        { 218,   9 }, // 41
        { 215,   7 }, // 42
        { 213,   5 }, // 43
        { 210,   4 }, // 44
        { 207,   2 }, // 45
        { 205,   1 }, // 46
        { 202,   0 }, // 47
        { 198,   0 }, // 48
        { 195,   0 }, // 49
        { 192,   0 }, // 50
        { 189,   1 }, // 51
        { 186,   2 }, // 52
        { 183,   3 }, // 53
        { 180,   4 }, // 54
        { 177,   5 }, // 55
        { 176,   7 }, // 56
        { 175,  11 }, // 57
        { 175,  14 }, // 58
        { 175,  17 }, // 59
        { 175,  20 }, // 60
        { 174,  23 }, // 61
        { 173,  26 }, // 62
        { 172,  29 }, // 63
        { 171,  32 }, // 64
		// right UNDERGLOW, temp copied from underglow
        { 169,  35 }, // 0
        { 167,  37 }, // 1
        { 165,  39 }, // 2
        { 163,  42 }, // 3
        { 162,  45 }, // 4
        { 161,  48 }, // 5
        { 161,  51 }, // 6
        { 161,  54 }, // 7
        { 163,  56 }, // 8
        { 167,  56 }, // 9
        { 170,  56 }, // 10
        { 173,  57 }, // 11
        { 176,  57 }, // 12
        { 179,  58 }, // 13
        { 182,  59 }, // 14
        { 185,  61 }, // 15
        { 188,  62 }, // 16
        { 191,  63 }, // 17
        { 194,  63 }, // 18
        { 197,  63 }, // 19
        { 200,  62 }, // 20
        { 203,  61 }, // 21
        { 204,  58 }, // 22
        { 206,  55 }, // 23
        { 207,  52 }, // 24
        { 208,  49 }, // 25
        { 210,  47 }, // 26
        { 212,  45 }, // 27
        { 215,  44 }, // 28
    },
    // LED flags (all 60)
    {
        // Left half
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,

		// Underglow Left (65 LEDs)
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,

		// UNDERGLOW left 29 LED
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,

        // Right half
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,

		// Underglow Right (65 LEDs)
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,

		// UNDERGLOW Right 29 LED
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW
    }
};
#endif


