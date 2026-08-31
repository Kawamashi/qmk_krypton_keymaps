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
#include "propergol.h"

#include "propergol_keycodes.h"
 //#include "features/modword.h"
//#include "../../modules/Kawamashi/layer_word/layer_word.h"
#include "../../../../modules/Kawamashi/oneshots_on_steroids/oneshots_on_steroids.h"
#include "../../../../modules/Kawamashi/clever_keys/clever_keys.h" 

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