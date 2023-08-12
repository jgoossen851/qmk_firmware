/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_ALPHAS_DVORAK = 0,
    LAYER_ALPHAS_QWERTY,
    LAYER_NUMPAD,
    LAYER_HEXPAD,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
    LAYER_FUNCTION,
    LAYER_POINTER,
    LAYER_TOOL,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER_OSL,
    LAYER_NAVIGATION_OSL,
    LAYER_MEDIA_OSL,
};

// Automatically enable sniping-mode on the pointer layer.
#define LAYER_MASK(layer) ((layer_state_t)1 << layer)
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK ( LAYER_MASK(LAYER_POINTER) | LAYER_MASK(LAYER_POINTER_OSL) )

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif      // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define OSM_SFT OSM(MOD_LSFT)
// #define OSM_CTL OSM(MOD_LCTL)
#define OSL_SYM OSL(LAYER_SYMBOLS)
#define OSL_NUM OSL(LAYER_NUMERAL)
#define OSL_NAV OSL(LAYER_NAVIGATION)
#define OSL_PNT OSL(LAYER_POINTER)
#define OSL_FUN OSL(LAYER_FUNCTION)
#define OSL_MED OSL(LAYER_MEDIA)
#define OSL_TOL OSL(LAYER_TOOL)
#define OSL_PT2 OSL(LAYER_POINTER_OSL)
#define OSL_NV2 OSL(LAYER_NAVIGATION_OSL)
#define OSL_MD2 OSL(LAYER_MEDIA_OSL)
#define AST_ALT MT(KC_ASTR, MOD_LALT)

#define TO_ALPH TO(LAYER_ALPHAS_DVORAK) /* As the default layer remains on, this will also return to other base layers (e.g., QWERTY) */
#define TO_SYMB TO(LAYER_SYMBOLS)
#define TO_NUMB TO(LAYER_NUMERAL)
#define TO_NAVG TO(LAYER_NAVIGATION)
#define TO_PNTR TO(LAYER_POINTER)
#define TO_FUNC TO(LAYER_FUNCTION)
#define TO_MEDA TO(LAYER_MEDIA)
#define TO_NMPD TO(LAYER_NUMPAD)
#define TO_TOOL TO(LAYER_TOOL)

#define LNAV    LAYER_NAVIGATION
#define LMED    LAYER_MEDIA
#define LTOL    LAYER_TOOL

#define DF_DVK  DF(LAYER_ALPHAS_DVORAK)
#define DF_QWTY DF(LAYER_ALPHAS_QWERTY)
#define TG_HXPD TG(LAYER_HEXPAD)

// clang-format off
/** \brief Dvorak layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_ALPHAS_DVORAK                                                                 \
        KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,     KC_F,    KC_G,    KC_C,    KC_R,    KC_L, \
           KC_A,    KC_O,    KC_E,    KC_U,    KC_I,     KC_D,    KC_H,    KC_T,    KC_N,    KC_S, \
        KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,     KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, \
                          OSL_PNT,  KC_SPC, OSL_NAV,  OSL_NUM, OSL_SYM


/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_ALPHAS_QWERTY                                                                 \
           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, \
           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, \
                          OSL_PNT,  KC_SPC, OSL_NAV,  OSL_NUM, OSL_SYM

/** Convenience row shorthands. */
#define _REDO   LCTL(KC_Y)
#define _PASTE  LCTL(KC_V)
#define _COPY   LCTL(KC_C)
#define _CUT    LCTL(KC_X)
#define _UNDO   LCTL(KC_Z)

#define ___X________X__DEAD_HALF_ROW__X________X___  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ___X_______DEAD_KEYS_IV_______X___           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define          ___HOME_ROW_MODS_ACS_L___                    KC_LALT, KC_LCTL, KC_LSFT
#define          ___HOME_ROW_MODS_ACS_R___                    KC_RSFT, KC_RCTL, KC_LALT
#define ________________CLIPBOARD_L________________    _UNDO,    _CUT,   _COPY,  _PASTE,   _REDO
#define ________________CLIPBOARD_R________________    _REDO,    _CUT,   _COPY,  _PASTE,   _UNDO

/*
 * Layers used on the Charybdis Nano.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */


/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
#define LAYOUT_LAYER_NUMERAL                                                                   \
     KC_ESC,    KC_7,    KC_8,    KC_9,  KC_EQL,   KC_DEL, KC_SLSH,  KC_SPC, KC_PDOT, KC_BSPC, \
     KC_TAB,    KC_4,    KC_5,    KC_6, KC_MINS,  KC_COLN, ___HOME_ROW_MODS_ACS_R___,  KC_ENT, \
     KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,  XXXXXXX, TO_NUMB, TO_NAVG, TO_NMPD, KC_RGUI, \
                      OSL_PNT,    KC_0, OSL_NAV,  TO_NUMB, OSL_SYM


/**
 * \brief Number Pad layer.
 *
 * Tertiary left-hand layer has a hexadecimal number pad with digits in the same locations as
 * the digits on the Number Layer.
 * Numbers in this layer use the dedicated numpad keys; therefore, shifted symbols will not
 * work on this layer but Alt-codes can be used on Windows.
 */
#define LAYOUT_LAYER_NUMPAD                                                                    \
     KC_ESC, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS,   KC_DEL, TG_HXPD, KC_SPC,  KC_PDOT, KC_BSPC, \
     KC_TAB, KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS,  KC_COLN, ___HOME_ROW_MODS_ACS_R___, KC_PENT, \
    KC_PSLS, KC_KP_1, KC_KP_2, KC_KP_3, KC_PAST,   KC_NUM, TO_NMPD, TO_MEDA, OSL_SYM, KC_RGUI, \
                      OSL_PNT, KC_KP_0, OSL_NAV,  OSL_NUM, OSL_SYM


/**
 * \brief Hex Pad layer.
 *
 * Tertiary left-hand layer has a hexadecimal number pad with digits in the same locations as
 * the digits on the Number Layer. The digits A - C are on the outer column with the same
 * locations as F10 - F12 on the Function Layer and D - F are on the inner column.
 * Numbers in this layer use the dedicated numpad keys; therefore, shifted symbols will not
 * work on this layer but Alt-codes can be used on Windows.
 */
#define LAYOUT_LAYER_HEXPAD                                                                    \
       KC_C, _______, _______, _______,    KC_F,  _______, _______, _______, _______, _______, \
       KC_B, _______, _______, _______,    KC_E,  _______, _______, _______, _______, _______, \
       KC_A, _______, _______, _______,    KC_D,  _______, XXXXXXX, _______, _______, _______, \
                      _______, _______, _______,  _______, _______


/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                   \
     KC_ESC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,   KC_DEL, KC_SLSH, KC_QUES, XXXXXXX, KC_BSPC, \
     KC_TAB,  KC_DLR, KC_PERC, KC_CIRC, KC_MINS,  CAPSWRD, ___HOME_ROW_MODS_ACS_R___,  KC_ENT, \
    KC_LBRC, KC_EXLM,   KC_AT, KC_HASH, KC_RBRC,  KC_CAPS, TO_SYMB, TO_PNTR, OSL_FUN, KC_RGUI, \
                      OSL_PNT, TO_ALPH, OSL_NAV,  TO_NUMB, TO_SYMB


/**
 * \brief Function layer.
 *
 * Quaternary left-hand layer has function keys in the same locations as the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner column.
 * Layer is activated pressing both the secondary thumb key (symbols) and the right pinky
 * home-row key (pointer) key simultaneously.
 * App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
#define LAYOUT_LAYER_FUNCTION                                                                  \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,  XXXXXXX, XXXXXXX,  KC_APP, XXXXXXX, XXXXXXX, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,  XXXXXXX, ___HOME_ROW_MODS_ACS_R___, XXXXXXX, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,  XXXXXXX, TO_FUNC, TO_TOOL, TO_NUMB, KC_RGUI, \
                      OSL_PNT, TO_ALPH, OSL_NAV,  TO_NUMB, TO_SYMB


/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYOUT_LAYER_NAVIGATION                                                                \
     KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_DEL, KC_HOME,   KC_UP, KC_PGUP, KC_BSPC, \
     KC_TAB, ___HOME_ROW_MODS_ACS_L___, XXXXXXX,   KC_INS, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT, \
    KC_LGUI, OSL_MD2, TO_NUMB, TO_NAVG, XXXXXXX,  XXXXXXX,  KC_END, XXXXXXX, KC_PGDN, XXXXXXX, \
                      OSL_PT2, TO_ALPH, TO_NAVG,  TO_NUMB, TO_SYMB


/**
 * \brief Media layer.
 *
 */
#define LAYOUT_LAYER_MEDIA                                                                     \
    ___X________X__DEAD_HALF_ROW__X________X___,  XXXXXXX, KC_MSTP, KC_MPLY, XXXXXXX, XXXXXXX, \
    ___X________X__DEAD_HALF_ROW__X________X___,  KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, \
    XXXXXXX, TO_PNTR, TO_NMPD, TO_MEDA, XXXXXXX,  ___X________X__DEAD_HALF_ROW__X________X___, \
                      OSL_PT2, TO_ALPH, OSL_NV2,  TO_NUMB, TO_SYMB


/** \brief Mouse emulation and pointer functions. 
 *
 * Secondary right-hand layer
 */
#define LAYOUT_LAYER_POINTER(f)                                                                \
     KC_ESC, DPI_MOD, DRGSCRL, SNP_TOG, KC_WH_U,   KC_DEL, KC_WH_L, DRG_TOG, KC_WH_R, KC_BSPC, \
     KC_TAB, ___HOME_ROW_MODS_ACS_L___, KC_WH_D,   KC_INS, KC_BTN1, KC_BTN2, KC_BTN3,  KC_ENT, \
    KC_LGUI, f(LTOL), TO_SYMB, TO_PNTR, S_D_MOD,  ________________CLIPBOARD_R________________, \
                      TO_PNTR, TO_ALPH, OSL_NV2,  TO_NUMB, TO_SYMB


/**
 * \brief Tools layer.
 *
 */
#define LAYOUT_LAYER_TOOL                                                                      \
    ___X________X__DEAD_HALF_ROW__X________X___,   EE_CLR,  DF_DVK, DF_QWTY, XXXXXXX, QK_BOOT, \
    ___X________X__DEAD_HALF_ROW__X________X___,  ___X________X__DEAD_HALF_ROW__X________X___, \
    XXXXXXX, TO_NAVG, TO_FUNC, TO_TOOL, XXXXXXX,  ___X________X__DEAD_HALF_ROW__X________X___, \
                      OSL_PT2, TO_ALPH, OSL_NAV,  TO_NUMB, TO_SYMB


/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with an "Alphas" layer defined above, e.g.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_BASE)
 */
#define _ACS_L(kc1, kc2, kc3, kc4) LALT_T(kc1), LCTL_T(kc2), LSFT_T(kc3), ALGR_T(kc4)
#define _ACS_R(kc1, kc2, kc3, kc4) ALGR_T(kc1), RSFT_T(kc2), RCTL_T(kc3), LALT_T(kc4)
#define _LG(kc) LGUI_T(kc)
#define _RG(kc) RGUI_T(kc)
#define _HOME_ROW_MOD_GACS(                                                     \
    L00, L01, L02, L03, L04,   R05, R06, R07, R08, R09,                         \
    L10, L11, L12, L13, L14,   R15, R16, R17, R18, R19,                         \
    L20, L21, L22, L23, L24,   R25, R26, R27, R28, R29,                         \
    ...)                                                                        \
        L00,        L01, L02, L03, L04,           R05, R06, R07, R08,     R09,  \
        L10, _ACS_L(L11, L12, L13, L14),   _ACS_R(R15, R16, R17, R18),    R19,  \
    _LG(L20),       L21, L22, L23, L24,           R25, R26, R27, R28, _RG(R29), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_ALPHAS_DVORAK] = LAYOUT_wrapper(HOME_ROW_MOD_GACS(LAYOUT_LAYER_ALPHAS_DVORAK)),
  [LAYER_ALPHAS_QWERTY] = LAYOUT_wrapper(HOME_ROW_MOD_GACS(LAYOUT_LAYER_ALPHAS_QWERTY)),
  [LAYER_SYMBOLS]       = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_NUMERAL]       = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_NAVIGATION]    = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_POINTER]       = LAYOUT_wrapper(LAYOUT_LAYER_POINTER(OSL)),
  [LAYER_FUNCTION]      = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_MEDIA]         = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NUMPAD]        = LAYOUT_wrapper(LAYOUT_LAYER_NUMPAD),
  [LAYER_HEXPAD]        = LAYOUT_wrapper(LAYOUT_LAYER_HEXPAD),
  [LAYER_TOOL]          = LAYOUT_wrapper(LAYOUT_LAYER_TOOL),
  [LAYER_POINTER_OSL]   = LAYOUT_wrapper(LAYOUT_LAYER_POINTER(TO)),
  [LAYER_NAVIGATION_OSL]= LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_MEDIA_OSL]     = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
};
// clang-format on


/* Define user callbacks */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}


/* Layers */

void enable_numlock_first_time(void) {
    // First time executed, turn on Num Lock if the computer indicates it is off
    static bool firstTime = true;
    if (firstTime && !host_keyboard_led_state().num_lock)  {
        register_code(KC_NUMLOCK);
        unregister_code(KC_NUMLOCK);
        firstTime = false;
    }
}

/* Callback for layer functions, for users. */
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK
    charybdis_set_pointer_sniping_enabled(state & (CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK));
#    endif  // CHARYBDIS_AUTO_SNIPING_ON_LAYER_MASK
#endif      // POINTING_DEVICE_ENABLE
    switch (get_highest_layer(state)) {
        case LAYER_ALPHAS_DVORAK:
        case LAYER_ALPHAS_QWERTY:
            LED_OFF(LED_1);
            LED_OFF(LED_2);
            LED_OFF(LED_3);
            LED_OFF(LED_4);
            break;
        case LAYER_NAVIGATION:
        case LAYER_NAVIGATION_OSL:
        case LAYER_POINTER:
        case LAYER_POINTER_OSL:
            LED_OFF(LED_1);
            LED_ON(LED_2);
            LED_OFF(LED_3);
            LED_ON(LED_4);
            break;
        case LAYER_SYMBOLS:
        case LAYER_NUMERAL:
            LED_ON(LED_1);
            LED_OFF(LED_2);
            LED_ON(LED_3);
            LED_OFF(LED_4);
            break;
        case LAYER_NUMPAD:
            enable_numlock_first_time();
            // no break; use default lighting
        default:
            LED_ON(LED_1);
            LED_ON(LED_2);
            LED_ON(LED_3);
            LED_ON(LED_4);
            break;
    }
    return state;
}

/* Callback for default layer functions, for users. Called on keyboard initialization */
layer_state_t default_layer_state_set_user(layer_state_t state) {
    return state;
}


/* Caps Word */

#ifdef CAPS_WORD_ENABLE
void caps_word_set_user(bool active) {
    if (active) {
        // Do something when Caps Word activates.
    } else {
        // Do something when Caps Word deactivates.
    }
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_KP_1 ... KC_KP_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
#endif // CAPS_WORD_ENABLE


/* EEPROM */

void eeconfig_init_user(void) {}


/* One Shot Keys */

void oneshot_locked_mods_changed_user(uint8_t mods) {}
void oneshot_mods_changed_user(uint8_t mods) {}

void oneshot_layer_changed_user(uint8_t layer) {
  // On OSL activation, turn off other exclusively OSL layers to allow switching to a lower layer state.
  // As these layers can only be activated as one-shots, the desired return layer is still on somewhere below in the layer stack.
  if (layer != LAYER_POINTER_OSL)    { layer_off(LAYER_POINTER_OSL);    }
  if (layer != LAYER_NAVIGATION_OSL) { layer_off(LAYER_NAVIGATION_OSL); }
  if (layer != LAYER_MEDIA_OSL)      { layer_off(LAYER_MEDIA_OSL);      }
  if (!layer) {
    // Oneshot layer deactivated
  }
}


/* LED Indicators */

bool led_update_user(led_t led_state) {
    return true;
};


/* Pointing Device */
#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_user(void) {}

#    if defined(SPLIT_POINTING_ENABLE) && (POINTING_DEVICE_COMBINED)
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    return pointing_device_combine_reports(left_report, right_report);
}

#    else
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
#        ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#            ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#            endif // !RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
#        endif // !CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
    return mouse_report;
}
#    endif // !defined(SPLIT_POINTING_ENABLE) && (POINTING_DEVICE_COMBINED)
#endif // !POINTING_DEVICE_ENABLE


/* Customizing Functionality */


/* Happens before most anything is started. Good for hardware setup that you want running very early */
void keyboard_pre_init_user(void) {}

/* Happens midway through the firmware’s startup process. Hardware is initialized, but features may not be yet */
void matrix_init_user(void) {}


/* Happens at the end of the firmware’s startup process. This is where you’d want to put “customization” code, for the most part */
void keyboard_post_init_user(void) {}

/*
 * Whenever possible you should customize your keyboard by using process_record_*()
 * and hooking into events that way, to ensure that your code does not have a 
 * negative performance impact on your keyboard.
 */
void matrix_scan_user(void) {
#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_STARTUP_MODE);
#        endif // !RGB_MATRIX_ENABLE
    }
#    endif // !CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // !POINTING_DEVICE_ENABLE
}

/* 
 * This function gets called at the end of all QMK processing, before starting the next iteration
 * Similar to matrix_scan_*, these are called as often as the MCU can handle.
 * To keep your board responsive, it’s suggested to do as little as possible during these function calls,
 * potentially throtting their behaviour if you do indeed require implementing something special.
 */
void housekeeping_task_user(void) {

}

void suspend_power_down_user(void) {
    // code will run multiple times while keyboard is suspended
}

void suspend_wakeup_init_user(void) {
    // code will run on keyboard wakeup
}

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb_red();
#endif  // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif  // RGB_MATRIX_ENABLE
}
