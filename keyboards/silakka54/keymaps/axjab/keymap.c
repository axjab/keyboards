// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

// ADDD THIS ////////////////////////////
//
//
// ERROR:
// ftACTION_TAP_DANCE_DOUBLE(SHIFT, LOCK):
  // Sends the kc1 keycode when tapped once, kc2 otherwise.
  // When the key is held, the appropriate keycode is registered:
  // kc1 when pressed and held, kc2 when tapped once, then pressed and held.

  // TODO:
  // SHIFT needed in NAV + SELECT toggle
  // escape toggled B,NAV,GUI,MOS -> TD(ESC) or HOLD(ESC)?
  // hold ENTER for shift
  // pipe = B + ?
  // double quote dance
  //
  // FIGURE OUT BETA LAYER
  //
  // Cancelled:
  // GUI + pgup/pgdn: not straightforward, use GUI + U or I instead

  // DOCUMENT:
  // 1. TAB = NAV + KC_SPC
  // 2. NAV arrows in corner

#include QMK_KEYBOARD_H

// Layers
// ============================================================================
enum layer_names {
    A, B, NAV, GUI, MOS, SYS
};

// Custom keycodes
// ============================================================================
enum custom_keycodes {
    TEST_STRING = SAFE_RANGE,
};

// Tap Dance
// ============================================================================
enum tap_dance_names {
    LBRC,    // [ on single tap, ] on double tap
    QUOT,    // TODO: ' / ", `, ~
    ESC,     // TODO: escape + layer functionality
};

// Tap Dance definitions
// ============================================================================
tap_dance_action_t tap_dance_actions[] = {
    // once for [{, twice for ]}
    [LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC)
    // once for ', twice for "
    [QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO)
    // TODO: Advanced tap dance for ' / "
    // [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(...),
    // TODO: Advanced tap dance for ESC / layer behavior
    // [TD_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(...),
};

// Tap Dance functions
// ============================================================================
void dance_safety(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 5) {
        SEND_STRING("Safety dance!");
        reset_tap_dance(state);
    }
}

// Custom keycode handling
// ============================================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TEST_STRING:
            if (record->event.pressed) {
                SEND_STRING("QMK test string!");
            }
            return false;
    }

    return true;
}

// ============================================================================
// Keymap
// ============================================================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ALPHA
    [A] = LAYOUT(
        KC_0,       KC_1,    KC_2,    KC_3,     KC_4,    KC_5,            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_MINS,  KC_EQL,
        QK_GESC,    KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     TD(LBRC),
        QK_LEAD,    KC_A,    KC_S,    KC_D,     KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  TD(QUOT),
        KC_LCTL,    KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,
                                      MO(2)     KC_LGUI, ,    LT(1,KC_SPC),     KC_BSPC, KC_RSFT
                                //    SHIFT,    NAV,     GUI,              SPC,    BSPC,    SHIFT
    ),
    // BETA
    [B] = LAYOUT(
        KC_RPRN, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_P7, KC_P8, KC_P9, KC_P0, KC_LPRN, KC_RPRN,
        _______, _______, _______, _______, _______, _______, KC_P4, KC_P5, KC_P6, KC_EQL, KC_LBRC, KC_RBRC,
        _______, _______, KC_NO, KC_NO, _______, _______, KC_P1, KC_P2, KC_P3, KC_PDOT, _______, _______,
        _______, _______, _______, _______, _______, _______),
    // NAV
    [NAV] = LAYOUT(
        _______,_______,    _______,    _______,    _______,_______,    _______,_______,_______,_______,    _______,    _______,
        KC_NO,  KC_NO,      KC_UP,      KC_NO,      KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_NO,      KC_NO,      KC_PGUP,
        KC_NO,  KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_NO,      KC_UP,      KC_PGDN,
        KC_NO,  KC_NO,      KC_NO,      KC_NO,      KC_NO,  KC_NO,      KC_NO,  KC_NO,  KC_NO,  KC_LEFT,    KC_DOWN,    KC_RGHT,
                                        KC_NO,      KC_NO,  _______,    KC_TAB,  KC_NO,  KC_NO
    ),
    // GUI
    [GUI] = LAYOUT(
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
                                _______,_______,_______,    _______,_______,_______
    ),
    // MOS
    [MOS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______
    ),
    // SYS
    [SYS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______
    )
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif
