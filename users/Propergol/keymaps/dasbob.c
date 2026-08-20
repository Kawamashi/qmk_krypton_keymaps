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
#include "propergol.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_split_3x5_3(
      PG_VIRG, PG_EACU, PG_U,    PG_P,    PG_TIRE,                 PG_V,   PG_M,    PG_C,    PG_J,    PG_X,   
      P(PG_O), R(PG_A), M(PG_I), I(PG_N), PG_POIN,                 PG_G,   I(PG_T), M(PG_S), R(PG_R), P(PG_L),
      PG_Q,    PG_EGRV, PG_Y,    PG_H,    PG_B,                    PG_K,   PG_D,    PG_F,    PG_W,    OS_1DK,
                                 OS_SHFT, LT_E,   LT_MGC, LT_REPT, LT_SPC, OS_NUMR
    ),



    [_NUMBERS] = LAYOUT_split_3x5_3(
      // S(KC_4), S(KC_3) and S(PG_EGAL) are here to give easy access to ⅔, ¾ and ≠.
      PG_VIRG, PG_MOIN, PG_PLUS, PG_EURO, PG_PERC,                   PG_EXP,  PG_DEG,  PG_EGAL, S(PG_EGAL), NUMPAD, 
      P(KC_4), R(KC_3), M(KC_2), I(KC_1), PG_POIN,                   PG_IND,  I(KC_6), M(KC_7), R(KC_8),    P(KC_9),
      S(KC_4), S(KC_3), PG_H,    KC_5,    KC_PDOT,                   _______, PG_SLSH, PG_MOIN, PG_PLUS,    PG_ASTX,
                                 OS_SHFT, LT_0   , LT_BSPC, LT_NNBS, LT_SPC,  OS_NUMR
     ),


    [_SYMBOLS] = LAYOUT_split_3x5_3(
      PG_ACIR,    PG_LCBR, PG_RCBR, PG_DLR,  PG_PERC,                   PG_HASH, PG_DQUO, PG_EGAL,    ALGR(PG_J), PG_GRV, 
      ALGR(PG_O), PG_LPRN, PG_RPRN, PG_PVIR, PG_2PTS,                   PG_BSLS, PG_SLSH, M(PG_MOIN), PG_PLUS,    PG_ASTX,
      PG_INF,     PG_LSBR, PG_RSBR, PG_SUP,  PG_AROB,                   KC_NO,   PG_APOD, PG_ESPR,    PG_PIPE,    PG_TILD,
                                    OS_NUMR, KC_SPC,  LT_BSPC, _______, _______, OS_NUMR
    ),


    [_1DK] = LAYOUT_split_3x5_3(
       _______, _______, _______, _______, PG_X,                      _______, _______, _______, _______, _______,
       _______, _______, _______, PG_Z,    _______,                   _______, _______, _______, _______, _______,
       _______, PG_J,    _______, _______, _______,                   _______, _______, _______, _______, OS_1DK,
                                  _______, PG_ECIR, PG_AGRV, PG_APOS, PG_UNDS, OS_NUMR
     ),



    [_SHORTNAV] = LAYOUT_split_3x5_3(
      KC_BSPC, HOME,    KC_UP,   END,     KC_PGUP,                   CAPSLOCK, KC_DEL,     C(KC_DEL),  _______,   _______,
      SEL_ALL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   CAPSWORD, I(KC_BSPC), M(BACKWRD), R(KC_ENT), P(KC_ESC),
      UNDO,    CUT,     COPY,    PASTE,   REDO,                      CAPSLIST, KC_TAB,     S(KC_TAB),  SEL_LINE,  SEL_WORD,
                                 _______, KC_SPC,  LT_BSPC, NAVWORD, KC_BSPC,  _______
    ),


    [_WINMAN] = LAYOUT_split_3x5_3(
      _______, _______, OS_WINM, _______, _______,                   _______, LSG(KC_LEFT), G(KC_UP),   LSG(KC_RIGHT), _______,
      P_MOD,   R_MOD,   M_MOD,   I_MOD,   _______,                   _______, G(KC_LEFT),   G(KC_DOWN), G(KC_RIGHT),   _______,
      _______, _______, _______, _______, _______,                   _______, _______,      _______,    _______,       _______,
                                 _______, _______, _______, _______, _______, _______
    ),


    [_FUNCTIONS] = LAYOUT_split_3x5_3(
       _______,  PANIC,    KC_F12,   KC_F11,   KC_F10,                    KC_VOLU, _______,  _______,  _______,  _______, 
       P(KC_F4), R(KC_F3), M(KC_F2), I(KC_F1), KC_BRIU,                   KC_MUTE, I(KC_F6), M(KC_F7), R(KC_F8), P(KC_F9),
       QK_BOOT,  KC_NUM,   KC_SCRL,  KC_F5,    KC_BRID,                   KC_VOLD, KC_MPLY,  KC_MPRV,  KC_MNXT,  KC_SLEP, 
                                     _______,  KC_F10,  _______, FUNWORD, _______, _______
     ),

};