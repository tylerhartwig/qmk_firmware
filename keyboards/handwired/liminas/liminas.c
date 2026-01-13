#include "liminas.h"

#include "quantum.h"
#include <math.h>
#include "report.h"




#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    // Key-to-LED matrix mapping
    // Left half (rows 0-4), then right half (rows 5-9)
    {
        // Left half
        {  0,  1,  2,  3,  4,  5 },
        {  6,  7,  8,  9, 10, 11 },
        { 12, 13, 14, 15, 16, 17 },
        { 18, 19, 20, 21, 22, 23 },
        { 24, 25, 26, 27, 28, 29 },
        // Right half
        { 30, 31, 32, 33, 34, 35 },
        { 36, 37, 38, 39, 40, 41 },
        { 42, 43, 44, 45, 46, 47 },
        { 48, 49, 50, 51, 52, 53 },
        { 54, 55, 56, 57, 58, 59 }
    },
    // Physical LED positions (x, y) - range 0-224 for x, 0-64 for y
    {
        // Left half (LEDs 0-29)
        {  0,  0}, { 20,  0}, { 40,  0}, { 60,  0}, { 80,  0}, {100,  0},
        {  0, 16}, { 20, 16}, { 40, 16}, { 60, 16}, { 80, 16}, {100, 16},
        {  0, 32}, { 20, 32}, { 40, 32}, { 60, 32}, { 80, 32}, {100, 32},
        {  0, 48}, { 20, 48}, { 40, 48}, { 60, 48}, { 80, 48}, {100, 48},
		// Left Thumb Cluster
        {101, 52}, {108, 54}, {104, 50}, {102, 60}, {111, 58}, {111, 64},
        // Right half (LEDs 30-59)
        {124,  0}, {144,  0}, {164,  0}, {184,  0}, {204,  0}, {224,  0},
        {124, 16}, {144, 16}, {164, 16}, {184, 16}, {204, 16}, {224, 16},
        {124, 32}, {144, 32}, {164, 32}, {184, 32}, {204, 32}, {224, 32},
        {124, 48}, {144, 48}, {164, 48}, {184, 48}, {204, 48}, {224, 48},
		// Right Thumb Cluster
        {123, 52}, {116, 54}, {120, 50}, {122, 60}, {113, 58}, {113, 64}
    },
    // LED flags (all 60)
    {
        // Left half
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        // Right half
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};
#endif


