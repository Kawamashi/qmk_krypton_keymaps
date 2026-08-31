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


#include QMK_KEYBOARD_H
#include "keymap.h"
#include "propergol.h"

#include "propergol_keycodes.h"
 //#include "features/modword.h"
//#include "../../modules/Kawamashi/layer_word/layer_word.h"
#include "../../../../modules/Kawamashi/oneshots_on_steroids/oneshots_on_steroids.h"
#include "../../../../modules/Kawamashi/clever_keys/clever_keys.h" 


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_split_3x5_3(
      PG_VIRG, PG_EACU, PG_U,    PG_P,    PG_TIRE,                 PG_V,   PG_M,    PG_C,    PG_J,    PG_X,
      P(PG_O), R(PG_A), M(PG_I), I(PG_N), PG_POIN,                 PG_G,   I(PG_T), M(PG_S), R(PG_R), P(PG_L),
      PG_Q,    PG_EGRV, PG_Y,    PG_H,    PG_B,                    PG_K,   PG_D,    PG_F,    PG_W,    OS_1DK,
                                 OS_SHFT, LT_E,   LT_MGC, LT_REPT, LT_SPC, OS_RTHB
    ),


    [_NUMROW] = LAYOUT_split_3x5_3(
      PG_VIRG, REV_TAB, ALT_TAB, OS_WNUM, PG_PERC,                   PG_EXP,  PG_EGAL, KC_PDOT, PG_EURO, _______,
      P(KC_9), R(KC_8), M(KC_7), I(KC_6), PG_POIN,                   NUMWORD, I(KC_1), M(KC_2), R(KC_3), P(KC_4),
      PG_MOIN, PG_PLUS, PG_ASTX, PG_SLSH, TG_NUM,                    PG_IND,  KC_5,    PG_DEG,  _______, OS_1DK,
                                 OS_SHFT, LT_SPC,  NNB_SPC, KC_BSPC, LT_0,    OS_SYMB
     ),


    [_NUMROW_REV] = LAYOUT_split_3x5_3(
      PG_VIRG, _______, KC_PDOT, PG_EGAL, PG_PERC,                   PG_EXP,  _______, PG_DEG,  PG_EURO, OS_WNUM,
      P(KC_4), R(KC_3), M(KC_2), I(KC_1), PG_POIN,                   NUMWORD, I(KC_6), M(KC_7), R(KC_8), P(KC_9),
      PG_MOIN, PG_PLUS, PG_ASTX, PG_SLSH, TG_NUM,                    PG_IND,  KC_5,    _______, _______, OS_1DK,
                                 OS_SYMB, LT_0,    KC_BSPC, NNB_SPC, LT_SPC,  OS_NUM
     ),


    [_NUMPAD] = LAYOUT_split_3x5_3(
      PG_VIRG,    REV_TAB,    ALT_TAB,    OS_WNUM,    PG_PERC,                   PG_EXP,  KC_7,    KC_8,    KC_9,    PG_EURO,
      P(PG_MOIN), R(PG_PLUS), M(PG_ASTX), I(PG_SLSH), PG_POIN,                   NUMWORD, I(KC_4), M(KC_5), R(KC_6), P(KC_PDOT),
      PG_DEG,     _______,    PG_EGAL,    PG_H,       TG_NUM,                    PG_IND,  KC_1,    KC_2,    KC_3,    OS_1DK,
                                          OS_SHFT,    LT_SPC,  NNB_SPC, KC_BSPC, LT_0,    OS_SYMB
     ),


    [_SYMBOLS_PROPERGOL] = LAYOUT_split_3x5_3(
      // NNB_SPC is here to finish a numword (ex: `127 km`) with _NUMROW_REV.
      ALGR(PG_O), PG_TILD, PG_LSBR, PG_RSBR, PG_PERC,                   PG_ACIR, PG_LCBR, PG_RCBR, PG_DLR,  PG_GRV,
      PG_MOIN,    PG_PLUS, PG_ASTX, PG_SLSH, PG_BSLS,                   PG_HASH, PG_LPRN, PG_RPRN, PG_PVIR, PG_DQUO,
      ALGR(PG_J), PG_INF,  PG_SUP,  PG_EGAL, PG_AROB,                   _______, PG_2PTS, PG_ESPR, PG_PIPE, PG_APOD,
                                    OS_NUM,  KC_SPC,  KC_BSPC, _______, NNB_SPC, OS_RTHB
    ),


    [_SYMBOLS_ERGOL] = LAYOUT_split_3x5_3(
      // NNB_SPC is here to finish a numword (ex: `127 km`) with _NUMROW_REV.
      PG_ACIR, PG_INF,  PG_SUP,  PG_DLR,  PG_PERC,                   PG_AROB, PG_ESPR,    PG_ASTX, PG_APOD, PG_GRV,
      PG_LCBR, PG_LPRN, PG_RPRN, PG_RCBR, PG_EGAL,                   PG_BSLS, PG_PLUS,    PG_MOIN, PG_SLSH, PG_DQUO,
      PG_TILD, PG_LSBR, PG_RSBR, PG_UNDS, PG_HASH,                   PG_PIPE, ALGR(PG_J), PG_PVIR, PG_2PTS, ALGR(PG_O),
                                 OS_NUM,  KC_SPC,  KC_BSPC, _______, NNB_SPC, OS_RTHB
    ),


    [_1DK] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, PG_X,                      _______, _______, _______, _______, _______,
      _______, _______, _______, PG_Z,    _______,                   _______, _______, _______, _______, _______,
      _______, PG_J,    _______, _______, _______,                   _______, _______, _______, _______, OS_1DK,
                                 _______, PG_ECIR, LT_AGRV, PG_APOS, PG_UNDS, OS_NUM
     ),



    [_SHORTNAV] = LAYOUT_split_3x5_3(
      KC_BSPC, HOME,    KC_UP,   END,     KC_PGUP,                   CAPSLOCK, PREV_WD,    KC_DEL,     NEXT_WD,   OS_WNAV,
      SEL_ALL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   CAPSWORD, I(KC_BSPC), M(BACKWRD), R(KC_ENT), P(KC_ESC),
      UNDO,    CUT,     COPY,    PASTE,   REDO,                      CAPSLIST, KC_TAB,     S(KC_TAB),  SEL_LINE,  SEL_WORD,
                                 _______, KC_SPC,  KC_BSPC, NAVWORD, KC_BSPC,  _______
    ),


    [_WINMAN] = LAYOUT_split_3x5_3(
      _______, LSG(KC_LEFT), G(KC_UP),   LSG(KC_RIGHT), _______,                   _______, _______, _______, _______, OS_WNAV,
      _______, G(KC_LEFT),   G(KC_DOWN), G(KC_RIGHT),   _______,                   _______, I_MOD,   M_MOD,   R_MOD,   P_MOD,
      _______, _______,      _______,    _______,       _______,                   _______, _______, _______, _______, _______,
                             _______,    _______,       _______, _______, _______, _______
    ),


    [_FUNCROW] = LAYOUT_split_3x5_3(
      _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_VOLU,                   KC_F10,  KC_F11,   KC_F12,   _______,  _______,
      P(KC_F9), R(KC_F8), M(KC_F7), I(KC_F6), KC_MUTE,                   KC_BRIU, I(KC_F1), M(KC_F2), R(KC_F3), P(KC_F4),
      KC_NUM,   KC_SCRL,  _______,  KC_SLEP,  KC_VOLD,                   KC_BRID, KC_F5,    _______,  _______,  QK_BOOT,
                                    _______,  PANIC,   FUNWORD, _______, _______, _______
     ),

    [_FUNCROW_REV] = LAYOUT_split_3x5_3(
      REV_TAB,  ALT_TAB,  KC_F12,   KC_F11,   KC_F10,                    KC_VOLU, KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,
      P(KC_F4), R(KC_F3), M(KC_F2), I(KC_F1), KC_BRIU,                   KC_MUTE, I(KC_F6), M(KC_F7), R(KC_F8), P(KC_F9),
      QK_BOOT,  _______,  _______,  KC_F5,    KC_BRID,                   KC_VOLD, KC_SLEP,  _______,  KC_SCRL,  KC_NUM,
                                    _______,  _______, _______, FUNWORD, PANIC,   _______
     ),

    [_FUNCPAD] = LAYOUT_split_3x5_3(
      KC_F1,    KC_F2,    KC_F3,    KC_F4,    _______,                   _______, KC_MNXT,    KC_VOLU,    KC_BRIU,    KC_NUM,
      P(KC_F5), R(KC_F6), M(KC_F7), I(KC_F8), _______,                   _______, I(KC_MPLY), M(KC_MUTE), R(KC_SLEP), P(KC_SCRL),
      KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,                   _______, KC_MPRV,    KC_VOLD,    KC_BRID,    QK_BOOT,
                                    _______,  PANIC,   FUNWORD, _______, _______, _______
     ),
};


void get_clever_keycode(uint16_t* ongoing_keycode, keyrecord_t* record) {

  uint16_t prev_keycode = get_recent_keycode(-1);

    // Apostrophe
    if (is_followed_by_apos(*ongoing_keycode, prev_keycode)) {
      set_last_keycode(PG_APOS);
    }
  
  switch (prev_keycode) {

    case NNB_SPC:
      switch (*ongoing_keycode) {

        // Capitalize punctuation after a thin non-breaking space
        case PG_POIN:
          // uses less space than process_word
          tap_code(KC_BSPC);
          invoke_key(SAGR(KC_SPC), record);
        case PG_TIRE:
        case PG_VIRG:
          return replace_ongoing_key(S(*ongoing_keycode), ongoing_keycode, record);
      }
      break;

    case KC_SPC:
      switch (get_recent_keycode(-2)) {
        case PG_EXCL:
        case PG_QUES:
        case PG_3PTS:
        case PG_POIN:
          // Capitalize the letter starting a new sentence.
          if (is_letter(*ongoing_keycode) || is_send_string_macro(*ongoing_keycode)) {
            set_oneshot_mods(MOD_BIT(KC_LSFT));     // Don't use weak mods !
          }
          break;
      }
      break;

    case PG_Q:
      switch (*ongoing_keycode) {
        
        // Automatically adds `u` after `q`
        case PG_ECIR:
        case PG_E:
        case PG_I:
        case PG_A:
        case PG_O:
        case PG_EACU:
        case PG_APOS:
          invoke_key(PG_U, record);
          update_bkspc_countdown(1);
          if (*ongoing_keycode == PG_ECIR) { return replace_ongoing_key(PG_ECIR, ongoing_keycode, record); }
          set_last_keycode(*ongoing_keycode);
          break;

        // "quoi"
        case PG_H:
          finish_word((uint16_t[]) {PG_U, PG_O, PG_I}, 3, ongoing_keycode, record);
          break;

        // "quand"
        case PG_N:
          return finish_word((uint16_t[]) {PG_U, PG_A, PG_N, PG_D}, 4, ongoing_keycode, record);
      }
      break;

    case PG_P:
      switch (*ongoing_keycode) {
        case PG_C:
          // "pas"
          return finish_word((uint16_t[]) {PG_A, PG_S}, 2, ongoing_keycode, record);
        
        case PG_J:
          // "pour"
          return finish_word((uint16_t[]) {PG_O, PG_U, PG_R}, 3, ongoing_keycode, record);

        case PG_X:
          // "plus"
          return finish_word((uint16_t[]) {PG_L, PG_U, PG_S}, 3, ongoing_keycode, record);
      }
      break;
    
    case PG_C:
      switch (*ongoing_keycode) {
        case PG_M:
          // "cm" -> "ch"
          update_bkspc_countdown(0);
          return replace_ongoing_key(PG_H, ongoing_keycode, record);

        case PG_J:
          // "cj" -> "ck"
          update_bkspc_countdown(0);
          return replace_ongoing_key(PG_K, ongoing_keycode, record);
      }
      break;
  }

  
  switch (*ongoing_keycode) {

    case MAGIC:
      switch (prev_keycode) {
        case PG_O:
          // "oui"
          invoke_key(PG_U, record);
        case PG_U:
          // "ui" SFB
          return replace_ongoing_key(PG_I, ongoing_keycode, record);

        case PG_EACU:
          // "éa" SFB
          return replace_ongoing_key(PG_A, ongoing_keycode, record);

        case PG_S:
          // "sc" SFB
          return replace_ongoing_key(PG_C, ongoing_keycode, record);

        case PG_C:
          // "cs" SFB
          return replace_ongoing_key(PG_S, ongoing_keycode, record);

        case PG_N:
          // "n." SFB
          return replace_ongoing_key(PG_POIN, ongoing_keycode, record);

        case PG_P:
          // "ph" SFB
          return replace_ongoing_key(PG_H, ongoing_keycode, record);

        case PG_G:
          // "gt" SFB
          return replace_ongoing_key(PG_T, ongoing_keycode, record);

        case PG_Q:
          // "qué" scissor
          invoke_key(PG_U,record);
          return replace_ongoing_key(PG_EACU, ongoing_keycode, record);

        case PG_Y:
          return replace_ongoing_key(PG_I, ongoing_keycode, record);

        case PG_T:
          // "tion"
          invoke_key(PG_I,record);
        case PG_I:
          // "ion"
          invoke_key(PG_O,record);
          return replace_ongoing_key(PG_N, ongoing_keycode, record);

        case PG_M:
          if (is_letter(get_recent_keycode(-2))) {
            // "ment"
            return finish_word((uint16_t[]) {PG_E, PG_N, PG_T}, 3, ongoing_keycode, record);
          } else {
            // "même"
            return finish_word((uint16_t[]) {PG_1DK, PG_E, PG_M, PG_E}, 4, ongoing_keycode, record);
          }

        case PG_B:
          // "beaucoup"
          return finish_word((uint16_t[]) {PG_E, PG_A, PG_U, PG_C, PG_O, PG_U, PG_P}, 7, ongoing_keycode, record);

        case PG_A:
          // "aujourd'hui"
          layer_off(_1DK);
          return finish_word((uint16_t[]) {PG_U, PG_J, PG_O, PG_U, PG_R, PG_D, PG_APOS, PG_H, PG_U, PG_I}, 10, ongoing_keycode, record);
        
        default:
          // "à"
          return replace_ongoing_key(PG_AGRV, ongoing_keycode, record);
      }

    case PG_EACU:
      if (prev_keycode == PG_E) {
        // "eé" -> "ez"
        update_bkspc_countdown(0);
        return replace_ongoing_key(PG_Z, ongoing_keycode, record);
      }
      break;

    case PG_EGRV:
      if (prev_keycode == PG_Y) {
          // "you" bad redirection
          invoke_key(PG_O,record);
          return replace_ongoing_key(PG_U, ongoing_keycode, record);
      }
      break;

    case KC_1 ... KC_0:
      if (should_use_numpad()) {
        // Replace numrow with numpad keycodes
        replace_ongoing_key(*ongoing_keycode + KC_P1 - KC_1, ongoing_keycode, record);
      }
      break;
  }
}