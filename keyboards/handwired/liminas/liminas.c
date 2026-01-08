#include "liminas.h"

#include "quantum.h"
#include <math.h>
#include "report.h"




#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        { 0, 1, 2, 3, 4, 5 }
    },
    {
        { 0,0 }, { 10, 0 }, { 20, 0 }, { 30, 0 }, { 40, 0 }, { 50, 0 }
    },
    {
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};
#endif


