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

// Correction automatique

#include "kawamashi.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = KAWA_LAYOUT(
      PG_EGRV, PG_EACU, PG_U,    PG_P,    PG_VIRG,                 PG_V,   PG_M,    PG_C,    PG_J,    PG_X,
      P(PG_O), R(PG_A), M(PG_I), I(PG_N), PG_POIN,                 PG_G,   I(PG_T), M(PG_S), R(PG_R), P(PG_L),
      PG_Q,    PG_TIRE, PG_Y,    PG_H,    KC_NO,                   KC_NO,  PG_D,    PG_F,    PG_W,    OS_1DK,
                                 OS_SHFT, LT_E,   LT_MGC, LT_REPT, LT_SPC, OS_NUM
    ),


    [_1DK] = KAWA_LAYOUT(
      PG_EACU, PG_J   , _______, N_TILD,  _______,                   _______, _______, _______, _______, _______,
      _______, _______, _______, PG_Z,    _______,                   _______, PG_K,    PG_W,    _______, _______,
      _______, PG_X,    _______, PG_H,    _______,                   _______, PG_B,    PG_D,    PG_S,    OS_1DK,
                                 _______, PG_ECIR, PG_AGRV, PG_APOS, LT_RSA,  OS_NUM
     ),


    [_NUMBERS] = KAWA_LAYOUT(
      PG_PLUS, PG_ASTX, PG_SLSH, PG_MOIN, PG_VIRG,                   PG_EXP,  _______, PG_DEG,  PG_EURO, TG_NUM,
      P(KC_4), R(KC_3), M(KC_2), I(KC_1), PG_POIN,                   PG_IND,  I(KC_9), M(KC_8), R(KC_7), P(KC_6),
      _______, PG_PERC, PG_H,    KC_5,    _______,                   _______, PG_2PTS, _______, _______, OS_1DK,
                                 OS_SHFT, LT_0   , LT_PDOT, NNB_SPC, LT_SPC,  OS_NUM
     ),


    [_SYMBOLS] = KAWA_LAYOUT(
      ALGR(KC_Q), PG_INF,  PG_SUP,  PG_MOIN, PG_BSLS,                  PG_ACIR, PG_LCBR, PG_RCBR, PG_DLR,  PG_GRV,
      PG_PLUS,    PG_ASTX, PG_SLSH, PG_EGAL, PG_POIN,                  PG_HASH, PG_LPRN, PG_RPRN, PG_PVIR, PG_DQUO,
      PG_TILD,    PG_PERC, PG_LSBR, PG_RSBR, _______,                  _______, PG_2PTS, PG_ESPR, PG_PIPE, PG_APOD,
                                    OS_NUM,  KC_SPC,  LT_MGC, LT_REPT, _______, OS_NUM
    ),


    [_SHORTNAV] = KAWA_LAYOUT(
      SEL_WORD,   SEL_LINE,   OS_WINM,    LGUI(PG_V), KC_VOLU,                   CAPSLOCK, C(KC_LEFT), KC_UP,      C(KC_RGHT), KC_PGUP,
      P(C(PG_A)), R(C(PG_X)), M(C(PG_C)), I(C(PG_V)), KC_VOLD,                   CAPSLIST, KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_PGDN,
      KC_MUTE,    KC_MUTE,    _______,    C(PG_Z),    _______,                   _______,  C(KC_PGUP), C(KC_PGDN), KC_NO,      OS_1DK,
                                          _______,    _______, _______, NAVWORD, _______,  _______
    ),


    [_WINMAN] = KAWA_LAYOUT(
      _______, _______, OS_WINM, _______, _______,                   _______, LSG(KC_LEFT), G(KC_UP),   LSG(KC_RIGHT), _______,
      P_MOD,   R_MOD,   M_MOD,   I_MOD,   _______,                   _______, G(KC_LEFT),   G(KC_DOWN), G(KC_RIGHT),   _______,
      _______, _______, _______, _______, _______,                   _______, _______,      _______,    _______,       _______,
                                 _______, _______, _______, _______, _______, _______
    ),


    [_FUNCTIONS] = KAWA_LAYOUT(
      _______,  _______,  KC_F12,   KC_F11,   KC_VOLU,                   KC_SCRL, _______,  OS_WNUM,  _______,  _______,
      P(KC_F4), R(KC_F3), M(KC_F2), I(KC_F1), KC_VOLD,                   KC_NUM,  I(KC_F9), M(KC_F8), R(KC_F7), P(KC_F6),
      KC_MUTE,  KC_MUTE,  _______,  KC_F5,    _______,                   _______, _______,  _______,  _______,  QK_BOOT,
                                    _______,  KC_F10,  FUNWORD, _______, _______, _______
     ),
};


// Combos

enum combos {
  R_BKSPC, 
  DELETE, 
  BK_WORD,
  L_BKSPC, 
  HOME, 
  END, 
  ENTER,
  TAB,
  ESC, 
  HELP, 
  PANIC,
  ALTTAB,
  ALTESC,
  L_SPACE
};

const uint16_t PROGMEM del_combo_d[] = {I(PG_T), M(PG_S), COMBO_END};
const uint16_t PROGMEM bkspc_combo_d[] = {M(PG_S), R(PG_R), COMBO_END};
const uint16_t PROGMEM bk_word_combo[] = {PG_C, PG_J, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {PG_P, PG_U, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {I(PG_N), M(PG_I), COMBO_END};
const uint16_t PROGMEM esc_combo[] = {I(PG_N), R(PG_A), COMBO_END};
const uint16_t PROGMEM bkspc_combo_g[] = {R(PG_A), M(PG_I), COMBO_END};
const uint16_t PROGMEM home_combo[] = {PG_TIRE, PG_Y, COMBO_END};
const uint16_t PROGMEM end_combo[] = {PG_U, PG_EACU, COMBO_END};
const uint16_t PROGMEM panic_combo[] = {PG_U, PG_C, COMBO_END};
const uint16_t PROGMEM alttab_combo[] = {PG_H, PG_Y, COMBO_END};
const uint16_t PROGMEM altesc_combo[] = {R(PG_A), M(PG_I), I(PG_N), COMBO_END};
const uint16_t PROGMEM space_combo[] = {PG_TIRE, PG_H, COMBO_END};

combo_t key_combos[] = {
    [R_BKSPC] = COMBO(bkspc_combo_d, KC_BSPC),
    [DELETE] = COMBO(del_combo_d, KC_DEL),
    [BK_WORD] = COMBO(bk_word_combo, LCTL(KC_BSPC)), 
    [L_BKSPC] = COMBO(bkspc_combo_g, KC_BSPC),
    [HOME] = COMBO(home_combo, KC_HOME),
    [END] = COMBO(end_combo, KC_END),
    [ENTER] = COMBO(enter_combo, KC_ENT),
    [TAB] = COMBO(tab_combo, KC_TAB),
    [ESC] = COMBO(esc_combo, KC_ESC),
    [PANIC] = COMBO(panic_combo, KC_NO),
    [ALTTAB] = COMBO(alttab_combo, KC_NO),
    [ALTESC] = COMBO(altesc_combo, LALT(KC_ESC)),
    [L_SPACE] = COMBO(space_combo, KC_SPC)
    };


bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {

    // Some combos should trigger regardless of the idle time.
    switch (combo_index) {
        case R_BKSPC:
        case BK_WORD:
        case ENTER:
        case HOME:
        case END:
        case L_SPACE:
          return true;

        default:
          //return enough_time_before_combo();    // takes more space
          if (get_idle_time() < IDLE_TIME_BEFORE_COMBO) { return false; }
    }
    return true;
}


void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
      case ALTTAB:
        if (pressed) {
            register_mods(MOD_LALT);
            tap_code(KC_TAB);
            layer_on(_SHORTNAV);
        } else {
            layer_off(_SHORTNAV);
            unregister_mods(MOD_LALT);
        }
        break;

      case PANIC:
        if (pressed) {
          if (!host_keyboard_led_state().num_lock) { tap_code(KC_NUM_LOCK); }
          if (!host_keyboard_led_state().scroll_lock) { tap_code(KC_SCROLL_LOCK); }
          
          if (get_layerword_layer() != 0) { disable_layerword(get_layerword_layer()); }
          layer_clear();
          set_use_numpad(false);
          set_shift_altgr(false);
          clear_oneshots_on_steroids();
          unregister_code(KC_LCTL);
          unregister_code(KC_LSFT);
          unregister_code(KC_LALT);
          unregister_code(KC_LGUI);
          //clear_weak_mods();
          if (get_modword() != idle) { disable_modword(get_modword()); }
          clear_recent_keys();
        }
        break;
  }
}

bool process_combo_key_repress(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
  switch (combo_index) {

      case ALTTAB:
        switch (keycode) {
          case PG_Y:
              tap_code16(S(KC_TAB));
              return true;
          case PG_H:
              tap_code(KC_TAB);
              return true;
        }
        break;
  }
  return false;
}


// Clever keys

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
        //case PG_POIN:
        case PG_D:
          // uses less space than process_word
          tap_code(KC_BSPC);
          invoke_key(SAGR(KC_SPC), record);
          return replace_ongoing_key(PG_2PTS, ongoing_keycode, record);
        case PG_EGRV:
          return replace_ongoing_key(PG_EXCL, ongoing_keycode, record);
        case PG_VIRG:
          return replace_ongoing_key(PG_QUES, ongoing_keycode, record);
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
/*         case PG_C:
          // "pas"
          return finish_word((uint16_t[]) {PG_A, PG_S}, 2, ongoing_keycode, record); */
        
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
    

    case PG_M:
    case PG_R:
    case PG_A:
    case PG_E:
    case PG_EACU:
    case PG_I:
    case PG_O:
    case PG_U:
    case PG_Y:
    case PG_EGRV:
    case A_CIRC:
      if (*ongoing_keycode == PG_H && IS_LAYER_OFF(_1DK)) {
          update_bkspc_countdown(0);
          return replace_ongoing_key(PG_B, ongoing_keycode, record);
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
          invoke_key(PG_U, record);
          return replace_ongoing_key(PG_EACU, ongoing_keycode, record);

        case PG_Y:
          // "you" bad redirection
          invoke_key(PG_O, record);
          return replace_ongoing_key(PG_U, ongoing_keycode, record);

        case PG_T:
          // "tion"
          invoke_key(PG_I, record);

        case PG_I:
          // "ion"
          invoke_key(PG_O, record);
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

        case PG_LPRN:
          // "();"
          invoke_key(PG_RPRN, record);
          return replace_ongoing_key(PG_PVIR, ongoing_keycode, record);

        case PG_RPRN:
          // ") {"
          invoke_key(KC_SPC, record);
          return replace_ongoing_key(PG_LCBR, ongoing_keycode, record);
        
        default:
          if (IS_LAYER_ON(_SYMBOLS)) { return replace_ongoing_key(prev_keycode, ongoing_keycode, record); }
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

    case U_CIRC:
      layer_off(_1DK);  //Otherwise, is_letter can't evaluate recents keycodes correctly
      if (prev_keycode == PG_O && !is_letter(get_recent_keycode(-2))) {
        update_bkspc_countdown(0);
        return replace_ongoing_key(PG_P, ongoing_keycode, record);
      }
      break;

    case N_TILD:
      return replace_ongoing_key(PG_H, ongoing_keycode, record);

    case KC_1 ... KC_0:
      if (should_use_numpad()) {
        // Replace numrow with numpad keycodes
        return replace_ongoing_key(*ongoing_keycode + KC_P1 - KC_1, ongoing_keycode, record);
      }
      break;

    case KC_LEFT:
      // ←
      return replace_ongoing_key(PG_APOD, ongoing_keycode, record);

    case KC_DOWN:
      // ↔
      return replace_ongoing_key(PG_APOS, ongoing_keycode, record);

    case KC_RIGHT:
      // →
      return replace_ongoing_key(PG_UNDS, ongoing_keycode, record);

    case PG_EGRV:
      if (get_shift_altgr()) { return replace_ongoing_key(PG_TIRE, ongoing_keycode, record); }
      break;

    case PG_N:
      if (get_shift_altgr()) { return replace_ongoing_key(PG_EGAL, ongoing_keycode, record); }
      break;

    case RSA(PG_TIRE):
      if (get_shift_altgr()) { return replace_ongoing_key(PG_Z, ongoing_keycode, record); }
      break;
  }
}


// Layer Word

uint8_t get_layerword_layer_from_trigger(uint16_t keycode) {

  switch (keycode) {
    case NUMWORD:
      return _NUMBERS;
    case NAVWORD:
      return _SHORTNAV;
    case FUNWORD:
      return _FUNCTIONS;
    default:
      return 0;
  }
}

uint16_t layerword_exit_timeout(uint8_t layer) {

  switch (layer) {
    case _NUMBERS:
    case _SHORTNAV:
        return 3000;
    case _FUNCTIONS:
        return 30000;
    default:
        return 0;
  }
}

bool should_continue_layerword(uint8_t layer, uint16_t keycode, keyrecord_t *record) {

  switch (layer) {

    case _NUMBERS:
      switch (keycode) {
        // Keycodes that should not disable numword.
        // Numpad keycodes
        case KC_1 ... KC_0:
        case KC_P1 ... KC_P0:
        case KC_PDOT:
        case PG_MOIN:
        case PG_ASTX: 
        case PG_PLUS:
        case PG_SLSH:
        case PG_EGAL:
        case PG_EXP:
        case PG_IND:
        case PG_H:
        case PG_2PTS:
        case NNB_SPC:
        case PG_POIN:
        case PG_VIRG:

        // Misc
        case KC_BSPC:
            return true; 
        default:
            return false;
      }

    case _SHORTNAV:
      switch (keycode) {
        case SEL_WORD:
        case SEL_LINE:
          return true;
      }
      keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
      switch (keycode) {
        case KC_LEFT:
        case KC_RIGHT:
        case KC_DOWN:
        case KC_UP:
        case KC_PGUP:
        case KC_PGDN:
        case KC_HOME:
        case KC_END:
            return true;
        default:
            return false;
      }

    case _FUNCTIONS:
      switch (keycode) {
        case KC_F1 ... KC_F12:
            return true;
        default:
            disable_layerword(_FUNCTIONS);
            return false;
      }
  }
  return false;
}