#include QMK_KEYBOARD_H
#include "keymap_dvorak_programmer.h"

#define _BASE 0
#define _SYM 1
#define _NAV 2

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define KC_ML MS_LEFT
#define KC_MR MS_RGHT
#define KC_MU MS_UP
#define KC_MD MS_DOWN
#define KC_MB1 MS_BTN1
#define KC_MB2 MS_BTN1

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)


#include "pointing_device.h"
#include "drivers/sensors/pmw3389.h"



void keyboard_post_init_user(void){
	debug_enable=true;
	debug_matrix=true;
	debug_mouse=true;

    // Force pointing device initialization
    pointing_device_init();
    wait_ms(100);

    // Set CPI explicitly
    pointing_device_set_cpi(3200);

    dprintf("Trackball initialized, CPI: %d\n", pointing_device_get_cpi());
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
	dprintf("In pointing_device_task_user\n");
    if (mouse_report.x != 0 || mouse_report.y != 0) {
        dprintf("Raw delta - X: %d, Y: %d\n", mouse_report.x, mouse_report.y);
    }

    static uint16_t debug_timer = 0;
    if (timer_elapsed(debug_timer) > 1000) {
        // Read motion register first
        uint8_t motion = pmw33xx_read(0, REG_Motion);

        if (motion & 0x80) { // Motion bit is set
            // Read all delta registers manually
            uint8_t dx_low = pmw33xx_read(0, REG_Delta_X_L);
            uint8_t dx_high = pmw33xx_read(0, REG_Delta_X_H);
            uint8_t dy_low = pmw33xx_read(0, REG_Delta_Y_L);
            uint8_t dy_high = pmw33xx_read(0, REG_Delta_Y_H);

            // Combine into 16-bit values
            int16_t raw_dx = (int16_t)((dx_high << 8) | dx_low);
            int16_t raw_dy = (int16_t)((dy_high << 8) | dy_low);

            dprintf("Motion: 0x%02X Raw DX: %d (%02X%02X) DY: %d (%02X%02X)\n",
                    motion, raw_dx, dx_high, dx_low, raw_dy, dy_high, dy_low);
        }

        debug_timer = timer_read();
    }
	return mouse_report;
}


void housekeeping_task_user(void) {

}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * +-----------------------------------------+                             +-----------------------------------------+
     * |   $  |   &  |   [  |   {  |   }  |   (  |                             |   *  |   )  |   +  |   ]  |   !  |   #  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | TAB  |   ;  |   ,  |   .  |   p  |   y  |                             |   f  |   g  |   c  |   r  |   l  |   /  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | ESC  |   a  |   o  |   e  |   u  |   i  |                             |   d  |   h  |   t  |   n  |   s  |   -  |
     * |------+------+------+------+-------------+                             +-------------+------+------+------+------+
     * |      |   '  |   q  |   j  |   k  |   x  |                             |   b  |   m  |   w  |   v  |   z  |      |
     * |------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |      |      |      |      |                             |      |      |      |      |
     *               +------+------+------+------+                             +------+------+------+------+
     *               |      |      |      |                                           |      |      |      |
     *               +------+      +------+                                           +------+      +------+
     */


    /*
    [_SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,

                          _______, _______, _______, _______,            _______, _______, _______, _______,
                          _______,          _______,                              _______,          _______
    )
    */
/*
    [_BASE] = LAYOUT(
        DP_DLR,  DP_AMPR,      DP_LBRC,      DP_LCBR,      DP_RCBR,      DP_LPRN,            DP_ASTR, DP_RPRN,         DP_PLUS,      DP_RBRC,      DP_EXLM,      DP_HASH,
        KC_TAB,  DP_SCLN,      DP_COMM,      DP_DOT,       DP_P,         DP_Y,               DP_F,    DP_G,            DP_C,         DP_R,         DP_L,         DP_SLSH,
        KC_ESC,  LCTL_T(DP_A), LALT_T(DP_O), LGUI_T(DP_E), LSFT_T(DP_U), DP_I,               DP_D,    RSFT_T(DP_H),    RGUI_T(DP_T), LALT_T(DP_N), RCTL_T(DP_S), DP_MINS,
        _______, DP_QUOT,      DP_Q,         DP_J,         DP_K,         DP_X,               DP_B,    DP_M,            DP_W,         DP_V,         DP_Z,         _______,

                               KC_BSPC,      OSL(_SYM),    _______,      _______,            _______, _______,         KC_ENT,  LT(_NAV,KC_SPC),
                               KC_TAB,                     _______,                                   _______,                  _______
    ),


    [_SYM] = LAYOUT(
        _______, _______, _______, _______, _______, DP_EQL,             DP_EQL,  _______, DP_SLSH, DP_ASTR, DP_MINS, _______,
        _______, _______, _______, _______, _______, _______,            _______, DP_1,    DP_2,    DP_3,    DP_PLUS, DP_AT,
        _______, _______, _______, _______, _______, _______,            _______, DP_4,    DP_5,    DP_6,    DP_PLUS, DP_BSLS,
        _______, _______, _______, _______, _______, _______,            _______, DP_7,    DP_8,    DP_9,    DP_DOT,  _______,

                          _______, _______, _______, _______,            _______, _______, _______, DP_0,
                          _______,          _______,                              _______,          _______
    ),


    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, KC_UP,   _______,  _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,  _______, _______,

                          _______, _______, _______, _______,            _______, _______, _______, _______,
                          _______,          _______,                              _______,          _______
    )
*/
};
