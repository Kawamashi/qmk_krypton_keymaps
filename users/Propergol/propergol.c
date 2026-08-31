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

#include "keymap.h"
#include "propergol.h"

#include "features/modword.h"
#include "../../modules/Kawamashi/layer_word/layer_word.h"
//#include "../../modules/Kawamashi/oneshots_on_steroids/oneshots_on_steroids.h"
//#include "../../modules/Kawamashi/clever_keys/clever_keys.h"

// Mod and layer tap configuration

static uint16_t next_keycode;
static keyrecord_t next_record;

bool get_speculative_hold(uint16_t keycode, keyrecord_t* record) {

    // Disable speculative hold during tapping sequences
    if (get_idle_time() < FLOW_TAP_INTERVAL) { return false; }
    // Disable speculative hold when any mods are already active
    // not to mess with hotkeys
    if (get_mods() | get_oneshot_mods()) { return false; }

    // Enable speculative holding for these keys.
    switch (keycode) {
        case I(PG_T):
        case I(PG_N):
            return true;
    }
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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_E:
            // Longer tapping term for LT_E, because it’s the only key not covered by Chordal Hold.
            return 300;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_E:
        case LT_SPC:
            // quick tap term to access _SYMBOLS easily after `E` or space
            return 150;
        default:
            return QUICK_TAP_TERM;
    }
}

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    // No "opposite hands" rule for LT_E
    LAYOUT_split_3x5_3(
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*', '*', 'R', '*'
    );

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                      uint16_t other_keycode, keyrecord_t* other_record) {
    // Exceptionally allow some one-handed chords for hotkeys.
    switch (tap_hold_keycode) {
        case LT_SPC:
            if (other_keycode == PG_X) {
                // to access _WINMAN with one hand
                return true;
            }
            break;
    }
    // Otherwise defer to the opposite hands rule.
    return get_chordal_hold_default(tap_hold_record, other_record);
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_E:
            // Disabling Permissive Hold for `E` when the other key is on the same side
            return approved_chord(keycode, record, next_keycode, &next_record);
        default:
            return true;
    }
}


// Housekeeping

void housekeeping_task_user(void) {
    modword_task();
}


// Key processing

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
      // Cache the next input for mod-tap decisions
      next_keycode = keycode;
      next_record  = *record;
  }
  return true;
}

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


// Feature configuration

// Numpad/numrow key switch

static bool use_numpad = false;

void set_use_numpad(bool target) {
  use_numpad = target;
}

bool should_use_numpad(void) {
  return use_numpad;
}


uint16_t tap_hold_extractor(uint16_t keycode) {

  switch (keycode) {
/*     case MOD_STB:
      return S(KC_TAB); */
    case M(BACKWRD):
      return BACKWRD;
    case P(PG_ASTX):
      return PG_ASTX;
    case R(PG_PLUS):
      return PG_PLUS;
    case LT_AGRV:
      return PG_AGRV;

    default:
      return keycode &= 0xff;
  }
}


static bool number_typed = false;
static bool nav_typed = false;

bool process_macros_I(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {

    switch (keycode) {
      case TG_NUM:
        use_numpad = !use_numpad;
        return false;

        #ifdef KRYPTON_THUMB_SHORTCUTS
      case KC_BSPC:
        if (IS_LAYER_ON(_SHORTNAV) && !nav_typed) { return process_layerword_triggers(NAVWORD, record); }
          //#ifndef KRYPTON_NUMBER_ROW_WITH_ONESHOT
        if (IS_LAYER_ON(_NUMBERS) && !number_typed) { return process_layerword_triggers(NUMWORD, record); }
          //#endif
        break;
        #endif
    }
      //#ifdef KRYPTON_THUMB_SHORTCUTS
    if (IS_LAYER_ON(_NUMBERS)) { number_typed = true; }
    if (IS_LAYER_ON(_SHORTNAV)) { nav_typed = true; }
      //#endif
  }

  if (record->tap.count) {
    // Special tap-hold keys (on tap).
    switch (keycode) {
      case LT_REPT:
        repeat_key_invoke(&record->event);
        return false;

      case LT_MGC:
        alt_repeat_key_invoke(&record->event);
        return false;

      case PANIC:
        if (record->event.pressed) {
          if (!host_keyboard_led_state().num_lock) { tap_code(KC_NUM_LOCK); }
          if (!host_keyboard_led_state().scroll_lock) { tap_code(KC_SCROLL_LOCK); }
          
          if (get_layerword_layer() != 0) { disable_layerword(get_layerword_layer()); }
          layer_clear();
          use_numpad = false;
          unregister_code(KC_LCTL);
          unregister_code(KC_LSFT);
          unregister_code(KC_LALT);
          unregister_code(KC_LGUI);
          //clear_weak_mods();
          if (get_modword() != idle) { disable_modword(get_modword()); }
          clear_recent_keys();
        }
        return false;
    }
  } else {
    switch (keycode) {

        #ifdef KRYPTON_NUMBER_ROW_WITH_ONESHOT
      case LT_REPT:
        if (record->event.pressed) {
          if (get_oneshot_on_steroids_state(OS_SHFT) > 0) {
            cancel_oneshot_on_steroids(OS_SHFT);
            register_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_ALGR));
            return false;
          }
        } else {
          if (get_mods() & MOD_BIT(KC_ALGR)) {
            unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_ALGR));
            return false;
          }
        }
        break;
        #endif
    }
  }
  return true; // Process all other keycodes normally
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (number_typed && IS_LAYER_OFF_STATE(state, _NUMBERS)) {
        number_typed = false;
    }
    if (nav_typed && IS_LAYER_OFF_STATE(state, _SHORTNAV)) {
        nav_typed = false;
    }
    return state;
}


bool process_macros_II(uint16_t keycode, keyrecord_t *record) {

  if (record->tap.count) {
    // Special tap-hold keys (on tap).
    switch (keycode) {
/*       case MOD_STB:
        return process_custom_tap_hold(S(KC_TAB), record); */
      case M(BACKWRD):
        return process_custom_tap_hold(BACKWRD, record);
      case M(PG_ASTX):
        return process_custom_tap_hold(PG_ASTX, record);
      case R(PG_PLUS):
        return process_custom_tap_hold(PG_PLUS, record);
      case LT_AGRV:
        return process_custom_tap_hold(PG_AGRV, record);
    }
  }

  if (record->event.pressed) {
    // Other macros (on press).
    switch (keycode) {
      case PG_DEG:
        tap_code(PG_1DK);
        tap_code(KC_0);
        return false;
      case HOME:
          #ifdef KRYPTON_MAC_MODIFIERS
        tap_code16(LCMD(KC_LEFT));
          #else
        tap_code(KC_HOME);
          #endif
        return false;
      case END:
          #ifdef KRYPTON_MAC_MODIFIERS
        tap_code16(LCMD(KC_RIGHT));
          #else
        tap_code(KC_END);
          #endif
        return false;
    }
  }
  return true; // Process all other keycodes normally
}


// Clever keys configuration

uint16_t get_ongoing_keycode_user(uint16_t keycode, keyrecord_t* record) {
  // Handles custom keycodes to be processed for Clever Keys

  if (is_send_string_macro(keycode)) { return keycode; }

  if (keycode == KC_BSPC) {
    // Setting the key to be repeated to match the key buffer.
    if (is_followed_by_apos(get_recent_keycode(-1), get_recent_keycode(-2))) {
        set_last_keycode(PG_APOS);
    } else {
        set_last_keycode(get_recent_keycode(-1));
    }
    return KC_NO;
  }

  switch (get_highest_layer(layer_state)) {

    case _1DK:
      switch (keycode) {
        case PG_Z:
        case PG_ECIR:
          return keycode;

        case PG_POIN:
          return PG_3PTS;
        case PG_U:
          return U_CIRC;
        case PG_A:
          return A_CIRC;

        default:
          if (is_letter(keycode)) { return LETTER_1DK; }
          return SYMBOL_1DK;
      }
    
    // There are no symbols on _SHORTNAV, _WINMAN or _FUNCTIONS
    case _SHORTNAV:
    case _WINMAN:
    case _FUNCTIONS:
      clear_recent_keys();
      return KC_NO;
  }

  switch (keycode) {
    case PG_E:    // because PG_E is not a basic keycode
      return keycode;
  }

  // Handles combos
  if (!IS_KEYEVENT(record->event)) {
    switch (keycode) {
      case KC_BSPC:
        return KC_TRNS;

      default:
        clear_recent_keys();
        return KC_NO;
    }
  }
  return KC_TRNS;
}


// Repeat and Magic keys

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {

  // Custom oneshots don't type anything on their own. They mustn't be remembered.
  if (is_oneshot_on_steroids(keycode)) { return false; }

  if (is_letter(tap_hold_extractor(keycode))) {
    // Forget Shift on letter keys when Shift or AltGr are the only mods.
    if ((*remembered_mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
      *remembered_mods &= ~MOD_MASK_SHIFT;
      return true;
    }
  }

  switch (keycode) {
    case KC_BSPC:
    case LT_REPT:
    case LT_MGC:
      return false;
    
    default:
      return true;
  }
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {

  if (get_last_keycode() == KC_NO) { return MAGIC; }

  switch (keycode) {
    case UNDO:
      return REDO;
    case REDO:
      return UNDO;
  }

  if (mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_ALGR))) {
    // regular behaviour of the alt-repeat key when a modifier
    // other than shift or alt-gr is registered
    return KC_TRNS;
  }

  keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
  switch (keycode) {
    // regular behaviour of the alt-repeat key for these keycodes
    case KC_LEFT:
    case KC_RIGHT:
    case KC_DOWN:
    case KC_UP:
    case KC_PGUP:
    case KC_PGDN:
    case KC_HOME:
    case KC_END:
      return KC_TRNS;
  }
  return MAGIC;
}


// One-shot on steroids

const oneshot_on_steroids_t oneshot_os[] = {
  {OS(OS_SHFT, OS_SHFT, MOD_BIT(KC_LSFT),                     0      )},
  {OS(OS_WNAV, LT_SPC,  0,                                   _WINMAN )},
  {OS(OS_WNUM, NUM_KEY, MOD_BIT(KC_LGUI),                     0      )},
  {OS(OS_1DK,  OS_1DK,  0,                                   _1DK    )},
  {OS(OS_NUM,  OS_NUM,  0,                                   _NUMBERS)},
  {OS(OS_SYMB, OS_SYMB, 0,                                   _SYMBOLS)},
  {OS(OS_RAS,  OS_RTHB, MOD_BIT(KC_LSFT) | MOD_BIT(KC_ALGR),  0      )}
};

bool is_oneshot_on_steroids_custom_behavior(uint16_t keycode, keyrecord_t* record) {

  if (record->event.pressed) {
    const uint8_t mods = get_mods() | get_oneshot_mods();
    switch (keycode) {

        #ifndef KRYPTON_NUMBER_ROW_WITH_ONESHOT
      case OS_SYMB:
        //const uint8_t mods = get_mods() | get_oneshot_mods();
        if (mods & MOD_MASK_SHIFT) {
          // OS_SYMB when shifted -> oneshot shift + alt-gr
          return process_record_oneshots_on_steroids(OS_RAS, record);
        }
        break;
          #endif

      case OS_1DK:
        // Custom behavior when alt-gr
        //const uint8_t mods = get_mods() | get_oneshot_mods();
        if (mods & MOD_BIT(KC_ALGR)) {
            tap_code16(ALGR(PG_1DK));
            return false;
        }
        break;

        #ifdef KRYPTON_THUMB_SHORTCUTS
      case LT_REPT:
        const int8_t os_shift_state = get_oneshot_on_steroids_state(OS_SHFT);
        if (os_shift_state == 1 || os_shift_state == 3) {
            return toggle_modword(capsword, CAPSWORD, record);
        }
        break;
        #endif
    }
  }
  return true;
}

bool is_oneshot_on_steroids_cancel_key(uint16_t keycode) {
    switch (keycode) {
      case PANIC:
        return true;
      default:
        return false;
    }
}

bool should_oneshot_on_steroids_ignore_key(uint16_t keycode, uint16_t oneshot, keyrecord_t* record) {

  const uint8_t mods = get_mods() | get_oneshot_mods();
  if (keycode == OS_1DK && (mods & MOD_BIT(KC_ALGR))) { return false; }

  bool is_mod_key = is_oneshot_mod_on_steroids(keycode);
  bool is_layer_key = is_oneshot_layer_on_steroids(keycode);
  
  if (!record->tap.count) {
    if (IS_QK_MOD_TAP(keycode)) { is_mod_key = true; }
    if (IS_QK_LAYER_TAP(keycode)) { is_layer_key = true; }
  }

  if (!is_mod_key && !is_layer_key) { return false; }

  // Mod or layer-change key pressed after an OSoS key
  if (is_oneshot_layer_on_steroids(oneshot)) {
    // OS_1DK and OS_NUM shouldn’t deactivate each other
    if (oneshot == OS_1DK && keycode == OS_NUM) { return true; }
    if (oneshot == OS_1DK && keycode == LT_AGRV) { return true; }
    if (oneshot == OS_NUM && keycode == OS_1DK) { return true; }
    // If a layer-change key is pressed after a OSL, the OSL must be reset.
    if (is_layer_key) { return false; }
    // keycode is not a layer key, it’s a mod key.
#     ifdef OS_MOD_SHOULD_LEAVE_OS_LAYER
    // When using OSM as Callum mods, an OSL tapped before must be reset.
    if (is_oneshot_mod_on_steroids(keycode)) { return false; }
#     endif  // OS_MOD_SHOULD_LEAVE_OS_LAYER
    // Standard behavior, like any mod key after an OSL
    return true;
  } else {
    // one-shot is OSM on steroids
#     ifdef OS_STEROIDS_ABSORB_MODS
    if (is_oneshot_layer_on_steroids(keycode)) {
        if (should_oneshot_on_steroids_absorb_mods(keycode)) { return false; }
    }
#     endif  // OS_STEROIDS_ABSORB_MODS
    // OSM on steroids should stay pressed
    // whether keycode is a mod or a layer-change key.
    return true;
  }
}

bool should_oneshot_on_steroids_deactivate_layer(uint16_t keycode, uint8_t layer) {
    switch (keycode) {
        case OS_1DK:
          // OS_1DK shouldn’t deactivate other layers
          // for ex. to be combined with _NUMBERS
          return false;
        default:
            return true;
    }
}


// Tap-hold utilities

bool on_left_hand(keypos_t pos) {
#ifdef SPLIT_KEYBOARD
  return pos.row < MATRIX_ROWS / 2;
#else
  return (MATRIX_COLS > MATRIX_ROWS) ? pos.col < MATRIX_COLS / 2
                                     : pos.row < MATRIX_ROWS / 2;
#endif
}

bool bilateral_combination(const keyrecord_t* tap_hold_record, const keyrecord_t* other_record) {
  return on_left_hand(tap_hold_record->event.key) != on_left_hand(other_record->event.key);
}

// By default, use the BILATERAL_COMBINATIONS rule to consider the tap-hold key
// "held" only when it and the other key are on opposite hands.
__attribute__((weak)) bool approved_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                                           uint16_t other_keycode, keyrecord_t* other_record) {
  return bilateral_combination(tap_hold_record, other_record);
}

bool process_custom_tap_hold(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {    // On press
      tap_code16(keycode);
      return false;
  }
  return true;
}

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
        // to access _NUMBERS from _1DK
        if (IS_QK_LAYER_TAP(keycode) && !record->tap.count) { return true; }

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