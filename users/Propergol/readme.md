# QMK Krypton keymap for Propergol

&nbsp;</br>
<p align="center">
<img src="../../png/Common/logo Krypton.png" width="200">
</p>

&nbsp;</br>
## Philosophy

[Propergol](https://github.com/Kawamashi/Propergol) is a great layout, but it needs 4 dedicated thumb keys (for `Space`, `E`, `Repeat` and `Alt-Repeat`). [Nordrassil](https://github.com/empressabyss/nordrassil/tree/main) needs 4 as well, [Magic Roll](https://github.com/Brooklyn-Style/Magic_Roll) 3. Cramming such layouts into a 36-keys keyboard can be quite a challenge. Krypton is my take on this issue. 

I don’t pretend Krypton is perfect, only you can imagine the layout that suits you the best! I designed Krypton as a solid starting point for those who want to try Propergol without spending hours figuring out the keyboard configuration to use with it. I’ve done my best to make it easy for you to customize Krypton and tailor it to your specific needs.

*Tweak it until you love it!*

&nbsp;</br>
## Layers

### Base layer

<img src="../../png/Propergol/base.png" width="900">

- Secondary layers (for navigation, number and function keys) are activated with [Layer Tap](https://docs.qmk.fm/feature_layers) keys under the thumbs.
- Krypton’s default configuration uses [Home-Row Modifiers](https://precondition.github.io/home-row-mods#what-are-home-row-mods) ([HRM](#Modifier-keys)) to make typing shortcuts more comfortable. Users of 6-column keyboards can disable them by commenting out `#define KRYPTON_ENABLE_HRM` in `config_propergol.h`.
- MacOS users can adapt the configuration by commenting out `#define KRYPTON_MAC_MODIFIERS` in `config_propergol.h`.
- To improve typing experience, Krypton uses a [One Shot](https://docs.qmk.fm/one_shot_keys) Shift key. This key should be used to capitalize letters, while [Shift on the home-row](https://precondition.github.io/home-row-mods#shift-thumb-keys) should be reserved for shortcuts. 
- Similarly, the Symbols Layer is activated with a One Shot layer key. It’s possible to swap the Symbols, Functions and Numbers keys if you prefer to use a one shot key for numbers. To do so, uncomment `#define KRYPTON_NUMBER_ROW_WITH_ONESHOT` in `config_propergol.h`.

<details>
<summary>One shot for Numbers layer</summary>
<img src="../../png/Propergol/base alt.png" width="900">
</details>

&nbsp;</br>
### 1DK layer

<img src="../../png/Propergol/1dk.png" width="820">

Instead of relying solely on Propergol’s driver, the [dead key](https://github.com/Kawamashi/Propergol/blob/main/README.md#la-touche-morte-de-propergol) is implemented as a layer, activated with a [One Shot on Steroids](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids) key. This makes the 1DK system much more flexible:
- You can customize the 1DK layer without having to modify the driver itself.
- If you tapped `★` by mistake, just tap it again to cancel it.
- Holding `★` allows you to chain several characters from the 1DK layer.
- `Repeat` can repeat a character from the 1DK layer.
- The 1DK layer can be made compatible with other QMK features such as [Caps Word](https://docs.qmk.fm/features/caps_word) and Clever Keys.
- If desired, Shift can be applied to the character following the dead key. For example, `Shift` `★` `O` can be used to type `Ô`. To do so,  uncomment `#define ONE_DEAD_KEY_DEFFERED_SHIFT` in `config_propergol.h`.

&nbsp;</br>
### Navigation layer

<img src="../../png/Common/nav layer.png" width="820">

This layer is activated by holding either thumb home key, on the base layer as well as on Numbers and Symbols layers.

The left half provides:
- Navigation keys (arrows, `Home`/`End`, `Page Up`/`Page Down`)
- Common keyboard shortcuts (`Cut`, `Copy`, `Paste`, `Undo`, `Redo` and `Select All`), allowing you to keep your right hand on the mouse.

The right half provides:
- Editing keys (`Backspace` under the right thumb and index finger home positions, `Delete`, `Enter`, `Escape`, `Tab` and `Shift-Tab`)
- Word-by-word navigation and deletion macros, as well as shortcuts for [selecting words and lines](https://github.com/Kawamashi/qmk_krypton_keymaps/tree/main#word-selection)
- [`Caps Word`](https://docs.qmk.fm/features/caps_word), [`Caps List`](https://github.com/Kawamashi/qmk_krypton_keymaps/tree/main#caps-list) and `Caps Lock`
- `Nav Word`, to type sequences of navigation keys without having to keep the layer-tap key held. This key triggers a [Layer Word](https://github.com/Kawamashi/qmk_modules/tree/main/layer_word) that remains active as long as you type navigation keys.
- A one shot Windows Management key, to activate the [Windows Management layer](#Windows-Management-layer) using [Lobre’s Shaka Gesture](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids#split-trigger-and-hold-keys)

&nbsp;</br>
### Numbers

Krypton’s default configuration uses a a numpad-style Numbers layer:

<details open>
<summary>Numpad</summary>
<img src="../../png/Common/numpad layer.png" width="820">
</details>

In addition to the number keys, the layer provides:
- `★`, to type alternate symbols, like fractions and arithmetic operators (`½`, `⅓`, `×`, `÷`, `±`, etc.)
- `Num Word`, to type sequences of numbers without having to keep the layer-tap key held. This key triggers a [Layer Word](https://github.com/Kawamashi/qmk_modules/tree/main/layer_word) that remains active as long as you type numeric symbols.
- `Previous`/`Next Window` keys (equivalent to `Alt+Tab` or `⌘+Tab`) on left hand, allowing you to switch between windows without pressing `Alt` or `⌘`. This functionality is implemented with [Cyclotab](https://getreuer.info/posts/keyboards/cyclotab/).
- A one shot `Win Num` key, to type easily `GUI`+ numbers, using [Lobre’s Shaka Gesture](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids#split-trigger-and-hold-keys)
- A `Toggle Num` key to switch between number-row and numpad keycodes (some applications require one or the other)

&nbsp;</br>
You can also use a number-row layout instead of the default numpad layout:

<details open>
<summary>Numrow</summary>
<img src="../../png/Common/numrow layer.png" width="820">

To enable it, uncomment `#define KRYPTON_NUMBER_ROW` in `config_propergol.h`.
</details>

&nbsp;</br>
Finally, the Symbols and Numbers keys can be swapped if you prefer to activate the Numbers layer with a one shot key:

<details>
<summary>Numrow + one shot key </summary>
<img src="../../png/Common/numrow-os layer.png" width="820">

To enable it, uncomment `#define KRYPTON_NUMBER_ROW_WITH_ONESHOT` in `config_propergol.h`.
</details>

&nbsp;</br>
### Symbols

<img src="../../png/Common/symbols layer.png" width="820">

Krypton uses [Propergol’s Symbols layer](https://github.com/Kawamashi/Propergol/blob/main/README.md#propergol-pour-la-programmation). The symbol positions are optimized for both symbol frequency and comfort of typing common symbol sequences. To do so, the layer minimizes same-finger bigrams while prioritizing comfortable rolls. 

A one-shot key provides access to the Numbers layer, making it easy to type symbols/numbers combinations such as `(0)` or `[1]`.

If Shift is active when you press the Symbols layer key, you will get the characters using Shift + AltGr instead.
<details>
<summary>Shift + AltGr Symbols</summary>
<img src="../../png/Common/symbols layer ext.png" width="820">
</details>

If you prefer, you can use the Ergo-L Symbols layer instead, by uncommenting `#define KRYPTON_ERGOL_SYMBOLS` in `config_propergol.h`.

&nbsp;</br>
### Fonction keys

<details open>
<summary>FuncPad</summary>
<img src="../../png/Common/funcpad layer.png" width="900">
</details>

This layer provides :
- function and media keys, following the same layout as the Numbers layer
- `Func Word`, to type sequences of function keys without having to keep the layer-tap key held. This key triggers a [Layer Word](https://github.com/Kawamashi/qmk_modules/tree/main/layer_word) that remains active as long as you type function keys.
- A `Panic` key, which restores the keyboard to its default state by disabling anything that might have been activated accidentally (one shot keys, Layer Words, Caps Word, Clever Keys, etc.).

<details>
<summary>FuncRow</summary>
<img src="../../png/Common/funcrow layer.png" width="900">
</details>

<details>
<summary>FuncRow + one shot key for numbers</summary>
<img src="../../png/Common/funcrow-os layer.png" width="900">
</details>

&nbsp;</br>
### Windows Management layer

<img src="../../png/Common/winman  layer.png" width="900">

As the name suggests, this layer allows you to manage your windows. The implementation is intentionally minimal, so feel free to add keys to suit your needs.
It’s activated with a [Shaka Gesture](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids#split-trigger-and-hold-keys) from the [Navigation layer](#Navigation-layer). Another press on the Windows Management key brings you back to this layer.


&nbsp;</br>
## Tap-Hold keys configuration

### Mod-tap keys

Krypton uses [Timeless Home-Row Modifiers](https://www.reddit.com/r/ErgoMechKeyboards/comments/1q1jo3c/urobs_zmk_timeless_home_row_mods_ported_to_native/). It’s the most thoughtfully designed configuration I've come across. This setup definitively resolved the issues that some users were experiencing with the HRMs. 

Despite the name, Timeless HRM use several timers, but you don’t need to worry about them while typing. To activate a modifier, simply combine a mod-tap key with a key on the opposite half of the keyboard, and everything will work naturally. In case of same-hand [rolls](https://getreuer.info/posts/keyboards/glossary/index.html#roll) or during tap sequences, the hold behavior is inhibited.

Although HRMs are already configured in Krypton, I strongly encourage you to read the [original explanation](https://www.reddit.com/r/ErgoMechKeyboards/comments/1q1jo3c/urobs_zmk_timeless_home_row_mods_ported_to_native/) to understand how the different options work.

Timeless is designed to prevent both false positives (a modifier activating when it shouldn't) and false negatives (a modifier failing to activate when it should). If you experience any of these issues, try adjusting the relevant timer:
- false negatives (same-hand): reduce `TAPPING_TERM`
- false negatives (cross-hand): reduce `FLOW_TAP_TERM`
- false positives (same-hand): increase `TAPPING_TERM`
- false positives (cross-hand): Increase `FLOW_TAP_TERM`

Change only one timer at a time, then test your typing before making further adjustments. This way, you can tell which change improved the behavior.

MacOS users can enable the macOS modifier arrangement by uncommenting `#define KRYPTON_MAC_MODIFIERS` in `config_propergol.h`.

If you prefer not to use HRMs, you can disable them by commenting out `#define KRYPTON_ENABLE_HRM` in `config_propergol.h`. The different timers can be tuned in the same file. 

Finally, you can easily change the order of the HRMs across all layers by editing the following macros in `propergol.h`:
```c
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
```


### Layer-tap keys

The general philosophy for Propergol Layer-tap keys configuration relies on [`PERMISSIVE_HOLD`](https://docs.qmk.fm/tap_hold#permissive-hold) and [`CHORDAL_HOLD`](https://docs.qmk.fm/tap_hold#chordal-hold). `PERMISSIVE_HOLD` makes it easier to trigger the hold behavior of thumb keys. `CHORDAL_HOLD` prevents false activations in [rolls](https://getreuer.info/posts/keyboards/glossary/index.html#roll) involving thumb home-position keys. 


However, E needs special handling to allow hotkeys to be typed using only the left hand. Since `CHORDAL_HOLD` prevents same-hand activation, a different approach is needed: during tapping sequences, `PERMISSIVE_HOLD` is only activated if the key tapped after `E` is on the right half of the keyboard. It’s also activated for keys on the left half (except arrows) if no character has been typed for a certain amount of time. This `IDLE_TIME_BEFORE_PERMISSIVE_HOLD` duration can be tuned in `config_propergol.h`.

Experienced Propergol users can go further by defining `HOLD_PRIORITY_FOR_HOTKEYS` in `config_propergol.h`. When this option is enabled, `HOLD_ON_OTHER_KEY_PRESS` is activated for `E`, `Magic` and `Repeat` if no character has been typed for a certain amount of time. This `IDLE_TIME_BEFORE_HOLD_PRIORITY` duration can be tuned in `config_propergol.h`.

> [!WARNING]
> Do not use `HOLD_PRIORITY_FOR_HOTKEYS` while learning Propergol. Depending on your typing style and familiarity with the layout, this setting can cause frequent unintended layer activations.

&nbsp;</br>
In summary:
<table>
  <thead>
    <tr>
      <th>Options</th>
      <th>Space</th>
      <th>E</th>
      <th>Repeat</th>
      <th>Magic</th>
    </tr>
  </thead>
   <tr>
    <th>Tapping Term</th>
    <td>250 ms</td>
    <td>300 ms</td>
    <td>250 ms</td>
    <td>250 ms</td>
   </tr>
   <tr>
    <th>Permissive Hold</th>
    <td>Yes</td>
    <td>- if the next key is on the right half<br>
    - after IDLE_TIME_BEFORE_PERMISSIVE_HOLD</td>
    <td>Yes</td>
    <td>Yes</td>
   </tr>
   <tr>
    <th>Chordal Hold</th>
    <td>Yes</td>
    <td>No</td>
    <td>No</td>
    <td>No</td>
   </tr>
    <tr>
    <th>Hold On Other Keypress</th>
    <td>No</td>
    <td>with HOLD_PRIORITY_FOR_HOTKEYS<br>
    (exept for arrow keys)</td>
    <td>with HOLD_PRIORITY_FOR_HOTKEYS</td>
    <td>with HOLD_PRIORITY_FOR_HOTKEYS</td>
   </tr>
</table>
&nbsp;</br>


&nbsp;</br>
## Features

### One shot on steroids keys

For its one shot keys (`Shift`, `★`, Symbols or Numbers layer key, etc.) Krypton uses [One Shot on Steroids](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids) (OSoS) keys. Compared to standard QMK one shot keys, this implementation offers several advantages:
- [**Instant activation**](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids#how-one-shots-on-steroids-work): modifiers and layers are activated as soon as you press an OSoS key, without waiting for the tapping term to expire.
- [**Easy cancellation**](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids#cancelling-one-shots-on-steroids): if you tapped an OSoS key by mistake, just tap it again to cancel it.
- [**No layer-stack restrictions**](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids#one-shot-layers-freed-from-the-layer-stack): OSoS layer keys can bypass the usual layer-stack restrictions, allowing you to type symbols from the Numbers layer and numbers from the Symbols layer for example.
- [**Shaka Gesture compatibility**](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids#split-trigger-and-hold-keys): OSoS keys are compatible with the Shaka Gesture, which is a really nice way of changing the behavior of secondary layers.
- **Customizable behavior**: you can further customize OSoS keys to [“absorb” modifiers](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids#mod-absorbing-one-shot-layers) or to affect only the next keypress even if the OSoS key is still held down.


### Combos

- Les combos peuvent être un game-changer sur les claviers compacts, mais tout le monde n’aime pas. 
- La configuration embarque quelques combos (backspace, enter, tab, escape, alt-tab et PANIC), qui utilisent des touches hors de la rangée de repos.
Comme ça, vous pourrez vous faire votre opinion si vous n’avez jamais testé. 
- Si l’utilisation des combos vous parait naturelle, la configuration peut être optimisée. Ma configuration personnelle en utilise plus, ce qui me permet d’avoir une couche de navigation mieux adaptée à mes besoins.
- La combo alt-tab utilise le [*key repress*](https://docs.qmk.fm/features/combo#customizable-key-repress), ce qui permet de naviguer dans vos fenêtres en lâchant et en réappuyant sur `H` ou `Y` : en appuyant sur les deux touches en même temps on déclenche la combo, qui envoie Alt-tab au système. On peut ensuite se déplacer dans les fenêtres ouvertes en relâchant `H` et en réappuyant dessus. On peut faire la même chose dans l’autre sens avec 'Y'.

### Layer words
- numword, navword, funword
- facilement modifiables dans `customization.c`

### Caps word, caps list et caps lock

### Select Word, select line

`KRYPTON_THUMB_SHORTCUTS` 

### Clever Keys
Sentence case
