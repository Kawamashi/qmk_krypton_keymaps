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
      PG_Q,    PG_EGRV, PG_Y,    PG_H,    KC_NO,                   KC_NO,  PG_D,    PG_F,    PG_W,    OS_1DK,
                                 OS_SHFT, LT_E,   LT_MGC, LT_REPT, LT_SPC, OS_NUMR
    ),



    [_NUMROW] = LAYOUT_split_3x5_3(
      // S(KC_4), S(KC_3) and S(PG_EGAL) are here to give easy access to ⅔, ¾ and ≠.
      PG_VIRG, PG_MOIN, PG_PLUS, PG_EURO, PG_PERC,                   PG_EXP,  PG_DEG,  PG_EGAL, S(PG_EGAL), NUMPAD, 
      P(KC_4), R(KC_3), M(KC_2), I(KC_1), PG_POIN,                   PG_IND,  I(KC_6), M(KC_7), R(KC_8),    P(KC_9),
      S(KC_4), S(KC_3), PG_H,    KC_5,    _______,                   _______, PG_SLSH, PG_MOIN, PG_PLUS,    PG_ASTX,
                                 MT_NUMW, LT_0   , LT_PDOT, NNB_SPC, LT_SPC,  OS_NUMR
     ),


    [_SYMBOLS] = LAYOUT_split_3x5_3(
      PG_ACIR,    PG_LCBR, PG_RCBR, PG_DLR,  PG_PERC,                   PG_HASH, PG_DQUO, PG_EGAL,    ALGR(PG_J), PG_GRV, 
      ALGR(PG_O), PG_LPRN, PG_RPRN, PG_PVIR, PG_2PTS,                   PG_BSLS, PG_SLSH, M(PG_MOIN), PG_PLUS,    PG_ASTX,
      PG_INF,     PG_LSBR, PG_RSBR, PG_SUP,  _______,                   _______, PG_APOD, PG_ESPR,    PG_PIPE,    PG_TILD,
                                    OS_RAS,  KC_SPC,  OS_NUMR, OS_NUMR, _______, OS_NUMR
    ),


    [_NUMPAD] = LAYOUT_split_3x5_3(
      PG_VIRG,  PG_MOIN,  PG_PLUS,  PG_EURO,  PG_PERC,                   PG_EXP,  PG_DEG,   PG_EGAL,  _______,  NUMROW,
      P(KC_P4), R(KC_P3), M(KC_P2), I(KC_P1), PG_POIN,                   PG_IND,  I(KC_P6), M(KC_P7), R(KC_P8), P(KC_P9),
      _______,  _______,  PG_H,     KC_P5,    _______,                   _______, PG_SLSH,  PG_MOIN,  PG_PLUS,  PG_ASTX,
                                    MT_NUMW,  LT_P0  , LT_PDOT, NNB_SPC, LT_SPC,  OS_NUMR
     ),


    [_1DK] = LAYOUT_split_3x5_3(
       _______, PG_J   , _______, N_TILD,  PG_X,                      PG_W,    _______, _______, _______, _______,
       _______, _______, _______, PG_Z,    _______,                   _______, PG_K,    PG_Y,    PG_EACU, _______,
       _______, PG_LPRN, PG_RPRN, PG_H,    _______,                   _______, PG_B,    PG_D,    PG_S,    OS_1DK,
                                  _______, PG_ECIR, PG_AGRV, PG_APOS, PG_UNDS, OS_NUMR
     ),



    [_SHORTNAV] = LAYOUT_split_3x5_3(
      SEL_WORD,   SEL_LINE,   OS_WINM,    LGUI(PG_V), KC_VOLU,                   KC_PGUP, C(KC_LEFT), KC_UP,      C(KC_RGHT), CAPSLOCK,
      P(C(PG_A)), R(C(PG_X)), M(C(PG_C)), I(C(PG_V)), KC_VOLD,                   KC_PGDN, KC_LEFT,    KC_DOWN,    KC_RIGHT,   CAPSWORD,
      KC_MUTE,    KC_MUTE,    KC_F2,      C(PG_Z),    _______,                   _______, C(KC_PGUP), C(KC_PGDN), C(PG_W),    CAPSLIST,
                                          _______,    _______, _______, NAVWORD, _______, OS_WNUM
    ),


    [_FUNCAPPS] = LAYOUT_split_3x5_3(
      _______, _______, OS_WINM, _______, _______,                   _______, LSG(KC_LEFT), G(KC_UP),   LSG(KC_RIGHT), _______,
      P_MOD,   R_MOD,   M_MOD,   I_MOD,   _______,                   _______, G(KC_LEFT),   G(KC_DOWN), G(KC_RIGHT),   _______,
      _______, _______, _______, _______, _______,                   _______, _______,      _______,    _______,       _______,
                                 _______, _______, _______, _______, _______, _______
    ),


    [_FUNCTIONS] = LAYOUT_split_3x5_3(
       _______,  _______,  KC_F12,   KC_F11,   KC_VOLU,                   QK_BOOT, _______,  OS_WNUM,  _______,  _______, 
       P(KC_F4), R(KC_F3), M(KC_F2), I(KC_F1), KC_VOLD,                   KC_NUM,  I(KC_F6), M(KC_F7), R(KC_F8), P(KC_F9),
       KC_MUTE,  KC_MUTE,  _______,  KC_F5,    _______,                   _______, _______,  _______,  _______,  _______, 
                                     _______,  KC_F10,  FUNWORD, _______, _______, _______
     ),

};