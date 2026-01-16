#include QMK_KEYBOARD_H
#include "keymap_dvorak_programmer.h"
#include "sendstring_dvorak_programmer.h"

#define _BASE 0
#define _SYM 1
#define _NAV 2
#define _AUTO 3

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


#include "quantum.h"
#include "pointing_device.h"
#include "drivers/sensors/pmw3389.h"


static uint32_t key_timer;
static bool is_typing_idle = true;
static bool rgb_effect_is_idle = true;

void check_key_timer(void);
#ifdef RGB_TYPING_EFFECT
void process_rgb_typing_effect(void);
#endif

void keyboard_post_init_user(void){
	debug_enable=true;
	debug_matrix=true;
	debug_mouse=true;
}


void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case MS_BTN1...MS_BTN8:
			break;
		default:
			key_timer = timer_read32();
			is_typing_idle = false;
	}
}

void housekeeping_task_user(void) {
#ifdef RGB_TYPING_IDLE_TIMEOUT
	check_key_timer();
#endif
#ifdef RGB_TYPING_EFFECT
	process_rgb_typing_effect();
#endif
}

void check_key_timer(void) {
	if(timer_elapsed32(key_timer) >= RGB_TYPING_IDLE_TIMEOUT) {
		is_typing_idle = true;
	}
}

void process_rgb_typing_effect(void){
	if(rgb_effect_is_idle && is_typing_idle != rgb_effect_is_idle) {
		rgb_matrix_mode(RGB_TYPING_EFFECT);
		rgb_effect_is_idle = false;
	} else if (!rgb_effect_is_idle && is_typing_idle != rgb_effect_is_idle) {
		rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
		rgb_effect_is_idle = true;
	}
}


enum custom_keycodes {
	DRAG_SCROLL = SAFE_RANGE,

	// SQL Keys
	SS_SELECT,
	SS_WHERE,
	SS_MTZ,
	SS_VIEW,

	// Autofill Keys
};

bool set_scrolling = false;

#define SCROLL_DIVISOR_H 32.0
#define SCROLL_DIVISOR_V 32.0

float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
	// use left for scrolling
    scroll_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
    scroll_accumulated_v += (float)left_report.y / SCROLL_DIVISOR_V;

    left_report.h = -1 * (int8_t)scroll_accumulated_h;
    left_report.v = -1 * (int8_t)scroll_accumulated_v;

    scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
    scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

    left_report.x = 0;
    left_report.y = 0;

	// Also use right for scrolling
    if (set_scrolling) {
        scroll_accumulated_h += (float)right_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)right_report.y / SCROLL_DIVISOR_V;

        right_report.h = -1 * (int8_t)scroll_accumulated_h;
        right_report.v = -1 * (int8_t)scroll_accumulated_v;

        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        right_report.x = 0;
        right_report.y = 0;
    }

    return pointing_device_combine_reports(left_report, right_report);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case DRAG_SCROLL:
			set_scrolling = record->event.pressed;
			return false;

		// SQL Send String
		case SS_SELECT:
			if (record->event.pressed) { SEND_STRING("SELECT "); }
			return false;
		case SS_WHERE:
			if (record->event.pressed) { SEND_STRING("WHERE "); }
			return false;
		case SS_MTZ:
			if (record->event.pressed) { SEND_STRING("MATERIALIZED "); }
			return false;
		case SS_VIEW:
			if (record->event.pressed) { SEND_STRING("VIEW "); }
			return false;
	}

	return true;
}
bool caps_word_press_user(uint16_t keycode) {
   switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case DP_A:
        case DP_B:
        case DP_C:
        case DP_D:
        case DP_E:
        case DP_F:
        case DP_G:
        case DP_H:
        case DP_I:
        case DP_J:
        case DP_K:
        case DP_L:
        case DP_M:
        case DP_N:
        case DP_O:
        case DP_P:
        case DP_Q:
        case DP_R:
        case DP_S:
        case DP_T:
        case DP_U:
        case DP_V:
        case DP_W:
        case DP_X:
        case DP_Y:
        case DP_Z:
        case DP_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case DP_0:
        case DP_1:
        case DP_2:
        case DP_3:
        case DP_4:
        case DP_5:
        case DP_6:
        case DP_7:
        case DP_8:
        case DP_9:
        case KC_BSPC:
        case KC_DEL:
        case DP_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', 'R',

                  'L', 'L', 'L', 'L',            'R', 'R', 'R', '*',
                  'L',      'L',                      'R',      'R'
    );

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
					  uint16_t other_keycode,    keyrecord_t *other_record) {

	switch(tap_hold_keycode) {
		case LGUI_T(DP_E):
			switch(other_keycode) {
				case DP_K:
					return true;
				case DP_H;
					return false;
			}
		break;
	}

	return get_chordal_hold_default(tap_hold_record, other_record);
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
    [_BASE] = LAYOUT(
        DP_DLR,  DP_AMPR,      DP_LBRC,      DP_LCBR,      DP_RCBR,      DP_LPRN,            DP_ASTR, DP_RPRN,         DP_PLUS,      DP_RBRC,      DP_EXLM,      DP_HASH,
        KC_TAB,  DP_SCLN,      DP_COMM,      DP_DOT,       DP_P,         DP_Y,               DP_F,    DP_G,            DP_C,         DP_R,         DP_L,         DP_SLSH,
        KC_ESC,  LCTL_T(DP_A), LALT_T(DP_O), LGUI_T(DP_E), LSFT_T(DP_U), DP_I,               DP_D,    RSFT_T(DP_H),    RGUI_T(DP_T), LALT_T(DP_N), RCTL_T(DP_S), DP_MINS,
        CW_TOGG, DP_QUOT,      DP_Q,         DP_J,         DP_K,         DP_X,               DP_B,    DP_M,            DP_W,         DP_V,         DP_Z,         _______,

                               KC_BSPC,      OSL(_SYM),    _______,      _______,            _______, _______,         KC_ENT,  LT(_NAV,KC_SPC),
                               OSL(_AUTO),                 _______,                                   MS_BTN2,                          MS_BTN1
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
    ),

    [_AUTO] = LAYOUT(
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, SS_SELECT, _______,
        _______, _______, _______, _______, _______, _______,            _______,  SS_MTZ, SS_WHERE, SS_VIEW, _______, _______,

                          _______, _______, _______, _______,            _______, _______, _______, _______,
                          _______,          _______,                              _______,          _______
    )
};
