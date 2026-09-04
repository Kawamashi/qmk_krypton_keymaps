/* Copyright 2025 @Kawamashi
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


#include "kawamashi.h"


const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    CHORDAL_HOLD_KAWA_LAYOUT(
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', '*',
                       '*', 'L', '*', '*', 'R', '*'
    );

bool get_speculative_hold(uint16_t keycode, keyrecord_t* record) {

  // Disable speculative hold during tapping sequences
  if (get_idle_time() < FLOW_TAP_INTERVAL) { return false; }
  // Disable speculative hold when any mods are already active
  // not to mess with hotkeys
  if (get_mods() | get_oneshot_mods()) { return false; }
  
  // Enable speculative holding for these keys.
  if (keycode == I(PG_N)) { return true; }

  return false;  // Disable otherwise.
}

bool is_tapping_sequence(uint16_t keycode) {
  // To trigger Tap Flow, the last input must be a character,
  // the time between the keypresses must be lower than FLOW_TAP_INTERVAL
  // and the ongoing keypress must be on a layer used for characters with mod-tap keys on it
  if (get_recent_keycode(-1) == KC_NO) { return false; }
  if (get_idle_time() > FLOW_TAP_INTERVAL) { return false; }
  
  switch (get_highest_layer(layer_state)) {
    case _BASE:
    case _NUMBERS:
        return true;
    default:
        return false;
  }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_E:
        case LT_SPC:
            return 150;
        default:
            return QUICK_TAP_TERM;
    }
}


// Housekeeping

void housekeeping_task_user(void) {
  modword_task();
}


// Key processing

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // LT Repeat and Magic keys
  if (!process_macros_I(keycode, record)) { return false; }

  // Prefixed layers
  if (!process_prefixing_layers(keycode, record)) { return false; }

  // Clever keys
  process_clever_keys(keycode, record);

  // Caps Word
  if (!process_modword(keycode, record)) {return false; }

  // Other macros
  if (!process_macros_II(keycode, record)) { return false; }

  // Process all other keycodes normally
  return true;
}


// Keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = KAWA_LAYOUT(
      PG_EGRV, PG_EACU, PG_U,    PG_P,    PG_VIRG,                 PG_V,   PG_M,    PG_C,    PG_J,    PG_X,
      P(PG_O), R(PG_A), M(PG_I), I(PG_N), PG_POIN,                 PG_G,   I(PG_T), M(PG_S), R(PG_R), P(PG_L),
      PG_Q,    PG_TIRE, OS_2DK,  PG_H,    KC_NO,                   KC_NO,  PG_D,    PG_F,    PG_W,    OS_1DK,
                                 OS_SHFT, LT_E,   LT_MGC, LT_REPT, LT_SPC, OS_NUM
    ),


    [_NUMBERS] = KAWA_LAYOUT(
      PG_PERC, _______, KC_5,    PG_H,    PG_VIRG,                   PG_EXP,  _______, PG_DEG,  PG_EURO, TG_NUM,
      P(KC_6), R(KC_7), M(KC_8), I(KC_9), PG_POIN,                   PG_IND,  I(KC_1), M(KC_2), R(KC_3), P(KC_4),
      PG_PLUS, PG_ASTX, PG_SLSH, PG_MOIN, _______,                   _______, PG_2PTS, _______, _______, OS_1DK,
                                 OS_SHFT, LT_0   , LT_PDOT, NNB_SPC, LT_SPC,  OS_NUM
     ),


    [_SYMBOLS] = KAWA_LAYOUT(
      PG_PERC,    PG_INF,  PG_SUP,  PG_MOIN, PG_BSLS,                  PG_ACIR, PG_LCBR, PG_RCBR, PG_DLR,  PG_GRV,
      PG_PLUS,    PG_ASTX, PG_SLSH, PG_EGAL, PG_POIN,                  PG_HASH, PG_LPRN, PG_RPRN, PG_PVIR, PG_DQUO,
      ALGR(PG_J), PG_TILD, PG_LSBR, PG_RSBR, _______,                  _______, PG_2PTS, PG_ESPR, PG_PIPE, PG_APOD,
                                    OS_NUM,  KC_SPC,  LT_MGC, LT_REPT, _______, OS_NUM
    ),

/*         [_SYMBOLS] = KAWA_LAYOUT(
      ALGR(PG_O), PG_APOD, PG_LSBR, PG_RSBR, PG_PERC,                  PG_ACIR, PG_LCBR, PG_RCBR, PG_DLR,  PG_GRV,
      PG_ASTX,    PG_MOIN, PG_PLUS, PG_SLSH, PG_BSLS,                  PG_HASH, PG_LPRN, PG_RPRN, PG_PVIR, PG_DQUO,
      PG_TILD,    PG_PIPE, PG_ESPR, PG_2PTS, _______,                  _______, PG_EGAL, PG_SUP,  PG_INF,  ALGR(PG_J),
                                    OS_NUM,  KC_SPC,  LT_MGC, LT_REPT, _______, OS_NUM
    ), */


    [_1DK] = KAWA_LAYOUT(
      PG_VIRG, PG_J   , _______, N_TILD,  _______,                   _______, _______, _______, _______, _______,
      _______, _______, _______, PG_Z,    _______,                   _______, PG_K,    PG_W,    PG_EACU, _______,
      _______, PG_X,    _______, PG_H,    _______,                   _______, PG_B,    PG_D,    PG_S,    OS_1DK,
                                 _______, PG_ECIR, PG_AGRV, PG_APOS, PG_UNDS, OS_NUM
     ),


    [_2DK] = KAWA_LAYOUT(
      _______, _______, _______, _______, _______,                   _______, _______, _______, PG_EURO, _______,
      _______, _______, _______, _______, _______,                   _______, PG_LPRN, PG_RPRN, PG_PVIR, PG_Y,
      _______, PG_W,    OS_2DK,  _______, _______,                   _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______
     ),


    [_SHORTNAV] = KAWA_LAYOUT(
      SEL_WORD,   SEL_LINE,   OS_WINM,    LGUI(PG_V), KC_VOLU,                   CAPSLOCK, C(KC_LEFT), KC_UP,      C(KC_RGHT), KC_PGUP,
      P(C(PG_A)), R(C(PG_X)), M(C(PG_C)), I(C(PG_V)), KC_VOLD,                   CAPSLIST, KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_PGDN,
      KC_MUTE,    KC_MUTE,    KC_F2,      C(PG_Z),    _______,                   _______,  C(KC_PGUP), C(KC_PGDN), KC_NO,      KC_NO,
                                          _______,    _______, _______, NAVWORD, _______,  _______
    ),


    [_WINMAN] = KAWA_LAYOUT(
      _______, _______, OS_WINM, _______, _______,                   _______, LSG(KC_LEFT), G(KC_UP),   LSG(KC_RIGHT), _______,
      P_MOD,   R_MOD,   M_MOD,   I_MOD,   _______,                   _______, G(KC_LEFT),   G(KC_DOWN), G(KC_RIGHT),   _______,
      _______, _______, _______, _______, _______,                   _______, _______,      _______,    _______,       _______,
                                 _______, _______, _______, _______, _______, _______
    ),


    [_FUNCTIONS] = KAWA_LAYOUT(
      _______,  _______,  KC_F5,    _______,  KC_VOLU,                   KC_SCRL, _______,  OS_WNUM,  _______,  _______,
      P(KC_6),  R(KC_F7), M(KC_F8), I(KC_F9), KC_VOLD,                   KC_NUM,  I(KC_F1), M(KC_F2), R(KC_F3), P(KC_F4),
      KC_MUTE,  KC_MUTE,  _______,  _______,  _______,                   _______, KC_F11,   KC_F12,   _______,  QK_BOOT,
                                    _______,  KC_F10,  FUNWORD, _______, _______, _______
     ),
};