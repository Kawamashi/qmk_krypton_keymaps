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

#include "propergol.h"

bool is_letter(uint16_t keycode) {

  // Taking 1DK layer into account
  if (IS_LAYER_ON(_1DK)) {
    switch (keycode) {

      case PG_VIRG:
        return true;

      case PG_V:
      case PG_M:
      case PG_C:
      case PG_J:    // arrobe
      case PG_X:    // non-breaking hyphen
      case PG_G:    // greek dead key
      case PG_T:    // slash
      case PG_R:    // €
      case PG_L:    // £
      case PG_D:    // umlaut
      case PG_W:    // en dash
      case PG_B:    // parenthesis
      case PG_K:
        return false;
    }
  }

  switch (keycode) {
    case KC_A ... KC_F:
    case KC_H ... KC_P:
    case KC_R ... KC_S:
    case KC_U ... KC_Z:
    case PG_L:
    case PG_E:
    case PG_F:
    case PG_W:
    case PG_AGRV:
    case PG_EGRV:
    case PG_ECIR:
    case A_CIRC:
    case U_CIRC:
    case LETTER_1DK:
      return true;

    default:
      return false;
  }
}

bool is_send_string_macro(uint16_t keycode) {
  switch (keycode) {
    case MAGIC:
      return true;
    
    default:
      return false;
  }
}

bool is_followed_by_apos(uint16_t keycode, uint16_t prev_keycode) {
  
  switch (keycode) {
    case PG_L:
    case PG_T:
    case PG_D:
    case PG_C:
    case PG_N:
    case PG_S:
    case PG_M:
    case PG_Y:
    case PG_J:
    case PG_I:
      if (is_letter(prev_keycode)) { return false; }
    case PG_Q:
    case PG_U:
      return true;

    default:
      return false;
  }
}


// Mod Word

bool caps_word_press_user(uint16_t keycode) {

  if (IS_LAYER_ON(_1DK)) {
    switch (keycode) {  
      case PG_D:    // umlaut
      case PG_X:    // non-breaking hyphen
        return true;
    }
  }

  // Keycodes that continue Caps Word, with shift applied.
  if (is_letter(keycode) || is_send_string_macro(keycode)) {
    add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
    return true;
  } 

  switch (keycode) {
    // Keycodes that continue Caps Word, without shifting.
    case PG_1DK:
    case PG_UNDS:
    case PG_TIRE:
    case PG_SLSH:
    case KC_1 ... KC_0:
    case KC_P1 ... KC_P0:
    case KC_BSPC:
    case BACKWRD:
    case KC_DEL:
    case PG_APOS:
      return true;

    default:
      return false;  // Deactivate Caps Word.
    }
}


bool should_continue_caps_list(uint16_t keycode, keyrecord_t* record) {

    // Keycodes that continue Caps List, but not Caps Word.
    // These keycodes trigger the counter to deactivate Caps List.
    switch (keycode) {
      case KC_BSPC:
        return update_capslist_counter(-1);
      case PG_VIRG:
      case KC_SPC:
          return update_capslist_counter(1);
    }

    if (is_letter(keycode) || is_send_string_macro(keycode)) { return update_capslist_counter(1); }

    // This condition can't be merged with the previous one
    // because caps_word_press_user adds shift to letters and send-string macros.
    if (caps_word_press_user(keycode)) { return update_capslist_counter(1); }

    return false;  // Deactivate Caps List.
}


bool list_separator(void) {

    // Words that continue Caps List.
    if (get_recent_keycode(-1) == KC_SPC) {

        if (get_recent_keycode(-2) == PG_VIRG) { return true; }

        if (word_check((uint16_t[]) {KC_SPC, PG_E, PG_T}, 3, 2)) { return true; }

        if (word_check((uint16_t[]) {KC_SPC, PG_O, PG_U}, 3, 2)) { return true; }
    }
    return false;
}

void word_selection_press_user(uint16_t keycode) {

  switch (keycode) {
    case C(KC_LEFT):
        set_nb_word_selected(1);
        tap_code(KC_LEFT);
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case C(KC_RGHT):
        set_nb_word_selected(1);
        tap_code(KC_RGHT);
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case KC_LEFT:
        select_word(-1);
        set_weak_mods(MOD_BIT_LCTRL | MOD_BIT_LSHIFT);
        break;

    case KC_RIGHT:
        select_word(1);
        set_weak_mods(MOD_BIT_LCTRL | MOD_BIT_LSHIFT);
        break;

    case KC_DOWN:
        select_line(1);
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case KC_UP:
        select_line(-1);
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case HOME:
    case END:
        add_weak_mods(MOD_BIT_LSHIFT);
        break;

    case NAVWORD:
        break;

    default:
      disable_modword(selectword);
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
        return 0;
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
        case NNB_SPC:
          if (IS_LAYER_ON(_SYMBOLS)) { return false; }
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
        case HOME:
        case END:
            return true;
        default:
            return false;
      }

    case _FUNCTIONS:
      switch (keycode) {
        case KC_F1 ... KC_F12:
            return true;
        default:
            disable_layerword(_FUNCROW);
            return false;
      }
  }
  return false;
}


// 1DK key and layer

// Keep track of the 1DK, for the Repeat Key
static bool ongoing_1dk = false;

bool process_prefixing_layers(uint16_t keycode, keyrecord_t *record) {

    if (!record->event.pressed) { return true; }    // Nothing special happens on release

    if (ongoing_1dk) {
        if (get_repeat_key_count() > 0) { tap_code(PG_1DK); }
        ongoing_1dk = false;
    }

    // Handling keys and layers related to the One Dead Key (1DK)
    switch (keycode) {
        case PG_1DK:
          return insert_1dk(keycode);
    }

    if (IS_LAYER_ON(_1DK)) {
        // because of HRM on _NUM layer, to tap symbols like ⅔, ¾ etc.
        if (IS_QK_MOD_TAP(keycode) && !record->tap.count) { return true; }

        switch (keycode) {
            case PG_Z:
            case PG_Q:
            case PG_UNDS:
            case PG_APOS:
            case PG_AGRV:
            case PG_ECIR:
              return true;
            case PG_U:
                // handle `quê`
                if (get_recent_keycode(-1) == PG_Q) { return true; }
                
            default:
              return insert_1dk(keycode);
        }
    }
    return true;
}


bool insert_1dk(uint16_t keycode) {

  #ifdef ONE_DEAD_KEY_DEFFERED_SHIFT
    // Special behavior of PG_1DK when shifted
    // Shift must apply to the keycode following PG_1DK.
    const bool shift_mods = get_mods() & MOD_MASK_SHIFT;
    const bool shift_weak_mods = get_weak_mods() & MOD_MASK_SHIFT;
    const bool shift_oneshot_mods = get_oneshot_mods() & MOD_MASK_SHIFT;
    
    if (shift_oneshot_mods) { del_oneshot_mods(MOD_MASK_SHIFT); }
    if (shift_mods) { del_mods(MOD_BIT(KC_LSFT)); }
    if (shift_weak_mods) { del_weak_mods(MOD_MASK_SHIFT); }
  #endif  // ONE_DEAD_KEY_DEFFERED_SHIFT

    ongoing_1dk = true;
    tap_code(PG_1DK);
    
  #ifdef ONE_DEAD_KEY_DEFFERED_SHIFT
    if (shift_oneshot_mods) { set_oneshot_mods(MOD_BIT(KC_LSFT)); }    // Don't use weak mods !
    if (shift_mods) { add_mods(MOD_BIT(KC_LSFT)); }
    if (shift_weak_mods) { add_weak_mods(MOD_BIT(KC_LSFT)); }
  #endif  // ONE_DEAD_KEY_DEFFERED_SHIFT

    return keycode != PG_1DK;
}

bool is_ongoing_1dk(void) {
  return ongoing_1dk;
}