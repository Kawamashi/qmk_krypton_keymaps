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

#pragma once

#include QMK_KEYBOARD_H

#include "propergol_keycodes.h"
#include "features/modword.h"
#include "../../modules/Kawamashi/layer_word/layer_word.h"
#include "../../modules/Kawamashi/oneshots_on_steroids/oneshots_on_steroids.h"
#include "../../modules/Kawamashi/clever_keys/clever_keys.h"


enum layers {
    _BASE = 0,
    _1DK,
    _NUMROW,
    _NUMROW_REV,
    _NUMPAD,
    _SYMBOLS_PROPERGOL,
    _SYMBOLS_ERGOL,
    _SHORTNAV,
    _WINMAN,
    _FUNCROW,
    _FUNCROW_REV,
    _FUNCPAD
};

enum custom_keycodes {
  TG_NUM = SAFE_RANGE,
  NUMWORD,
  NAVWORD,
  FUNWORD,
  CAPSWORD,
  CAPSLIST,
  CAPSLOCK,
  SEL_WORD,
  SEL_LINE,
  OS_SHFT,
  OS_SYMB,
  OS_NUM,
  OS_1DK,
  OS_WNAV,
  OS_WNUM,
  OS_RAS,
  A_CIRC,
  U_CIRC,
  MAGIC,
  LETTER_1DK,
  SYMBOL_1DK,
  PG_DEG,
  HOME,
  END,
  PANIC
};

  // Layer changers

#ifdef KRYPTON_ERGOL_SYMBOLS
  #define _SYMBOLS _SYMBOLS_ERGOL
#else
  #define _SYMBOLS _SYMBOLS_PROPERGOL
#endif

#if defined KRYPTON_NUMBER_ROW
  // Numbers and function keys in rows
  #define _FUNCTIONS _FUNCROW
  #define _NUMBERS   _NUMROW
  #define  OS_RTHB    OS_SYMB
  #define  NUM_KEY    LT_MGC
  #define  LT_REPT    LT(_FUNCTIONS, KC_1)
  #define  LT_MGC     LT(_NUMBERS,   KC_1)
  // to combine _NUMBERS with _1DK
  #define  LT_AGRV    LT(_NUMBERS,   PG_AGRV)

#elif defined KRYPTON_NUMBER_ROW_WITH_ONESHOT
  // Numbers and function keys in rows, with a oneshot key to access the num layer
  #define _FUNCTIONS _FUNCROW_REV
  #define _NUMBERS   _NUMROW_REV
  #define  OS_RTHB    OS_NUM
  #define  NUM_KEY    OS_NUM
  #define  LT_REPT    LT(_SYMBOLS,   KC_1)
  #define  LT_MGC     LT(_FUNCTIONS, KC_1)
  #define  LT_AGRV    PG_AGRV

#else
  // Krypton base conf
  #define _FUNCTIONS _FUNCPAD
  #define _NUMBERS   _NUMPAD
  #define  OS_RTHB    OS_SYMB
  #define  NUM_KEY    LT_MGC
  #define  LT_REPT    LT(_FUNCTIONS, KC_1)
  #define  LT_MGC     LT(_NUMBERS,   KC_1)
  // to combine _NUMBERS with _1DK
  #define  LT_AGRV    LT(_NUMBERS,   PG_AGRV)
#endif

#define LT_SPC  LT(_SHORTNAV,  KC_SPC)
#define LT_E    LT(_SHORTNAV,  PG_E)
#define LT_0    LT(_SHORTNAV,  KC_0)
#define LT_RBKS LT(_FUNCTIONS, KC_BSPC)



  // Modifiers
#ifdef KRYPTON_ENABLE_HRM
  #ifdef KRYPTON_MAC_MODIFIERS
    #define P(k) LSFT_T(k)
    #define R(k) LCTL_T(k)
    #define M(k) LOPT_T(k)
    #define I(k) LCMD_T(k)
  #else
    #define P(k) LSFT_T(k)
    #define R(k) LALT_T(k)
    #define M(k) LGUI_T(k)
    #define I(k) LCTL_T(k)
  #endif
#else
  #define P(k) k
  #define R(k) k
  #define M(k) k
  #define I(k) k
#endif

#ifdef KRYPTON_MAC_MODIFIERS
  #define P_MOD KC_LSFT
  #define R_MOD KC_LCTL
  #define M_MOD KC_LOPT
  #define I_MOD KC_LCMD
#else
  #define P_MOD KC_LSFT
  #define R_MOD KC_LALT
  #define M_MOD KC_LGUI
  #define I_MOD KC_LCTL
#endif


// Hotkeys
#ifdef KRYPTON_MAC_MODIFIERS
  #define UNDO    LCMD(PG_Z)
  #define REDO    LSG(PG_Z)
  #define BACKWRD LOPT(KC_BSPC)
  #define SEL_ALL LCMD(PG_A)
  #define CUT     LCMD(PG_X)
  #define COPY    LCMD(PG_C)
  #define PASTE   LCMD(PG_V)
  #define PREV_WD LOPT(KC_LEFT)
  #define NEXT_WD LOPT(KC_RGHT)
  #define ALT_TAB LCMD(KC_TAB)
  #define REV_TAB LSG(KC_TAB)
  #define CYCLOTAB_KEYS LCMD(KC_TAB)
#else
  #define UNDO    LCTL(PG_Z)
  #define REDO    LCTL(PG_Y)
  #define BACKWRD LCTL(KC_BSPC)
  #define SEL_ALL LCTL(PG_A)
  #define CUT     LCTL(PG_X)
  #define COPY    LCTL(PG_C)
  #define PASTE   LCTL(PG_V)
  #define PREV_WD LCTL(KC_LEFT)
  #define NEXT_WD LCTL(KC_RGHT)
  #define ALT_TAB LALT(KC_TAB)
  #define REV_TAB LSA(KC_TAB)
#endif

// conf_words

// Returns true for macros used to type sequence of letters
bool is_send_string_macro(uint16_t keycode);

// Returns true for letters that can be followed by an apostrophe (in french)
bool is_followed_by_apos(uint16_t keycode, uint16_t prev_keycode);


// conf_features

// Returns true if `pos` on the left hand of the keyboard, false if right.
bool on_left_hand(keypos_t pos);

/**
 * Returns true if the args come from keys on opposite hands.
 *
 * @param tap_hold_record keyrecord_t from the tap-hold key's event.
 * @param other_record keyrecord_t from the other key's event.
 * @return True if the keys are on opposite hands.
 */
bool bilateral_combination(const keyrecord_t* tap_hold_record, const keyrecord_t* other_record);

/**
 * Optional callback to customize which key chords are considered "held".
 *
 * This callback is called if while `tap_hold_keycode` is pressed,
 * `other_keycode` is pressed. Return true if the tap-hold key should be
 * considered held, or false to consider it tapped.
 *
 * @param tap_hold_keycode Keycode of the tap-hold key.
 * @param tap_hold_record keyrecord_t from the tap-hold press event.
 * @param other_keycode Keycode of the other key.
 * @param other_record keyrecord_t from the other key's press event.
 * @return True if the tap-hold key should be considered held.
 */
bool approved_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record);

// Handles the tap function of tap-hold keys using non-basic keycodes
bool process_custom_tap_hold(uint16_t keycode, keyrecord_t *record);

// Set whether numbers from numrow are to be replaced by numbers from numpad 
void set_use_numpad(bool target);

// Returns whether numbers from numrow are to be replaced by numbers from numpad
bool should_use_numpad(void);

// This function extracts the base keycode of MT and LT,
// even if the tap/hold key is a custom one, with non-basic tap keycode.
uint16_t tap_hold_extractor(uint16_t keycode);

// Macros to be executed at the beginning of process_record_user :
// Layer-tap Repeat and Magic keys
bool process_macros_I(uint16_t keycode, keyrecord_t *record);

// Other macros, to be executed at the end of process_record_user
bool process_macros_II(uint16_t keycode, keyrecord_t *record);


// Prefixing Layers

/* Handler function for prefixing layers

 * My custom layout uses the One Dead Key (1DK) concept.
 * <https://github.com/OneDeadKey/1dk/blob/master/1dk.md>
 * In my keymap, I use a prefixing layer to implement it.
 * This approach allows more flexibility than to use the 1DK directly.
 * This way, on my 1DK layer, I can use macros or symbols that don’t need the 1DK.
 * 
 * I also use One Shot for All (OS4A) keys and layers. 
 * On their side of the keyboard, OS4A keys behave like one-shot layers, mainly to access Callum mods.
 * OS4A keys also act like one-shot shifts for the opposite side of the keyboard.
 * The latter behavior is implemented with a prefixing layer.
*/
bool process_prefixing_layers(uint16_t keycode, keyrecord_t *record);

// Adds the One Dead Key to the keys of the 1DK layer
// Also, possibility to apply shift to the key following the dead key :
// when I want to shift a key on the 1DK layer,
// I prefer to press shift then the one-shot key to the 1DK layer than the opposite.
bool insert_1dk(uint16_t keycode);

// Returns whether the 1DK is being sent
bool is_ongoing_1dk(void);