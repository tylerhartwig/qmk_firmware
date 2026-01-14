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
        {  0,  4,  8, 12, 16, 20 },
        {  1,  5,  9, 13, 17, 21 },
        {  2,  6, 10, 14, 18, 22 },
        {  3,  7, 11, 15, 19, 23 },
        { 24, 25, 26, 27, 28, 29 },
        // Right half
        { 30, 34, 38, 42, 46, 50 },
        { 31, 35, 39, 43, 47, 51 },
        { 32, 36, 40, 44, 48, 52 },
        { 33, 37, 41, 45, 49, 53 },
        { 54, 55, 56, 57, 58, 59 }
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
        // Right half (LEDs 30-53, column order)
        {124,  0}, {124, 16}, {124, 32}, {124, 48},  // Column 0
        {144,  0}, {144, 16}, {144, 32}, {144, 48},  // Column 1
        {164,  0}, {164, 16}, {164, 32}, {164, 48},  // Column 2
        {184,  0}, {184, 16}, {184, 32}, {184, 48},  // Column 3
        {204,  0}, {204, 16}, {204, 32}, {204, 48},  // Column 4
        {224,  0}, {224, 16}, {224, 32}, {224, 48},  // Column 5
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


