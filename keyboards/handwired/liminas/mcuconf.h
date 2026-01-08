#pragma once

#include_next <mcuconf.h>

// SPI for trackball
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 FALSE

#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 TRUE

// PIO for WS2812 LEDs
#undef RP_PWM_USE_PWM0
#define RP_PWM_USE_PWM0 FALSE
