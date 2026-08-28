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
                                 OS_SHFT, LT_E,   LT_MGC, LT_REPT, LT_SPC, OS_RTHB
    ),


    [_NUMROW] = LAYOUT_split_3x5_3(
      PG_VIRG, _______, _______, OS_WNUM, PG_PERC,                   PG_EXP,  PG_EGAL, KC_PDOT, PG_EURO, _______,
      P(KC_9), R(KC_8), M(KC_7), I(KC_6), PG_POIN,                   NUMWORD, I(KC_1), M(KC_2), R(KC_3), P(KC_4),
      PG_MOIN, PG_PLUS, PG_ASTX, PG_SLSH, TG_NUM,                    PG_IND,  KC_5,    PG_DEG,  _______, PG_1DK,
                                 OS_SHFT, LT_SPC,  NNB_SPC, KC_BSPC, LT_0,    OS_SYMB
     ),


    [_NUMROW_REV] = LAYOUT_split_3x5_3(
      PG_VIRG, _______, KC_PDOT, PG_EGAL, PG_PERC,                   PG_EXP,  _______, PG_DEG,  PG_EURO, OS_WNUM,
      P(KC_4), R(KC_3), M(KC_2), I(KC_1), PG_POIN,                   NUMWORD, I(KC_6), M(KC_7), R(KC_8), P(KC_9),
      PG_MOIN, PG_PLUS, PG_ASTX, PG_SLSH, TG_NUM,                    PG_IND,  KC_5,    _______, _______, PG_1DK,
                                 OS_SYMB, LT_0,    KC_BSPC, NNB_SPC, LT_SPC,  OS_NUM
     ),


    [_NUMPAD] = LAYOUT_split_3x5_3(
      PG_VIRG,    _______,    _______,    OS_WNUM,    PG_PERC,                   PG_EXP,  KC_7,    KC_8,    KC_9,    PG_EURO,
      P(PG_MOIN), R(PG_PLUS), M(PG_ASTX), I(PG_SLSH), PG_POIN,                   NUMWORD, I(KC_4), M(KC_5), R(KC_6), P(KC_PDOT),
      PG_DEG,     _______,    PG_EGAL,    PG_H,       TG_NUM,                    PG_IND,  KC_1,    KC_2,    KC_3,    PG_1DK,
                                          OS_SHFT,    LT_SPC,  NNB_SPC, KC_BSPC, LT_0,    OS_SYMB
     ),


    [_SYMBOLS] = KAWA_LAYOUT(
      ALGR(PG_O), PG_TILD, PG_LSBR, PG_RSBR, PG_PERC,                   PG_ACIR, PG_LCBR, PG_RCBR, PG_DLR,  PG_GRV,
      PG_MOIN,    PG_PLUS, PG_ASTX, PG_SLSH, PG_BSLS,                   PG_HASH, PG_LPRN, PG_RPRN, PG_PVIR, PG_DQUO,
      ALGR(PG_J), PG_INF,  PG_SUP,  PG_EGAL, _______,                   _______, PG_2PTS, PG_ESPR, PG_PIPE, PG_APOD,
                                    OS_NUMR, KC_SPC,  OS_NUMR, OS_NUMR, _______, OS_NUMR
    ),


    [_1DK] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, PG_X,                      _______, _______, _______, _______, _______,
      _______, _______, _______, PG_Z,    _______,                   _______, _______, _______, _______, _______,
      _______, PG_J,    _______, _______, _______,                   _______, _______, _______, _______, OS_1DK,
                                 _______, PG_ECIR, PG_AGRV, PG_APOS, PG_UNDS, OS_NUM
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
      _______,  _______,  KC_F12,   KC_F11,   KC_F10,                    KC_VOLU, KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,
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