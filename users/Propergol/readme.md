# QMK Krypton keymap for Propergol

<p align="center">
<img src="../../png/Common/logo Krypton.png" width="200">
</p>

## Philosophy

[Propergol](https://github.com/Kawamashi/Propergol) is a great layout, but it needs 4 dedicated thumb keys (for `Space`, `E`, `Repeat` and `Alt-Repeat`). [Nordrassil](https://github.com/empressabyss/nordrassil/tree/main) needs 4 as well, [Magic Roll](https://github.com/Brooklyn-Style/Magic_Roll) 3. Cramming such layouts into a 36-keys keyboard can be quite a challenge. Krypton is my take on this issue. 

I don’t pretend Krypton is perfect, only you can imagine the layout that suits you the best! I designed Krypton as a solid starting point for those who want to try Propergol without spending hours figuring out the keyboard configuration to use with it. I’ve done my best to make it easy for you to customize Krypton and tailor it to your specific needs.

*Tweak it until you love it!*


## Layers

### Base layer

<img src="../../png/Propergol/base.png" width="900">

- Secondary layers (for navigation, number and function keys) are activated with [Layer Tap](https://docs.qmk.fm/feature_layers) keys under the thumbs.
- Krypton’s default configuration uses [Home-Row Modifiers](https://precondition.github.io/home-row-mods#what-are-home-row-mods) (HRM) to make typing shortcuts more comfortable. Users of 6-column keyboards can disable them by commenting out `#define KRYPTON_ENABLE_HRM` in `config_propergol.h`.
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
- Navigation keys (arrows, Home/End, Page Up/Page Down)
- Common keyboard shortcuts (Cut, Copy, Paste, Undo, Redo and Select All), allowing you to keep your right hand on the mouse.

The right half provides:
- Editing keys (Backspace under the right thumb and index finger home positions, Delete, Enter, Escape, Tab and Shift-Tab)
- Word-by-word navigation and deletion macros, as well as shortcuts for [selecting words and lines](https://github.com/Kawamashi/qmk_krypton_keymaps/tree/main#word-selection).
- [Caps Word](https://docs.qmk.fm/features/caps_word), [Caps List](https://github.com/Kawamashi/qmk_krypton_keymaps/tree/main#caps-list) and Caps Lock
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
- `Num Word`, to type sequences of numbers without having to keep holding the layer-tap key. This key triggers a [Layer Word](https://github.com/Kawamashi/qmk_modules/tree/main/layer_word) that remains active as long as you type numeric symbols.
- Previous/Next Window keys (equivalent to Alt+Tab or ⌘+Tab) on left hand, allowing you to switch between windows without pressing `Alt` or `⌘`. This functionality is implemented with [Cyclotab](https://getreuer.info/posts/keyboards/cyclotab/).
- A one shot `Win Num` key, to type easily `GUI`+ numbers, using [Lobre’s Shaka Gesture](https://github.com/Kawamashi/qmk_modules/tree/main/oneshots_on_steroids#split-trigger-and-hold-keys)
- A `Toggle Num` key to switch between number-row and numpad keycodes (some applications require one or the other).

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

If `Shift` is active when you press the Symbols layer key, you will get the characters using `Shift` + `AltGr` instead.
<details>
<summary>Shift + AltGr Symbols</summary>
<img src="../../png/Common/symbols layer ext.png" width="820">
</details>

If you prefer, you can use the Ergo-L Symbols layer instead, by uncommenting `#define KRYPTON_ERGOL_SYMBOLS` in `config_propergol.h`.


### Fonctions

- Touches de fonctions et touches média (vol ±, mute, play/pause, previous/next, etc)
- Les touches sont arrangées en fonction de la couche de nombres choisie.
- FUNWORD et PANIC. PANIC permet de remettre le clavier dans sa configuration par défaut, en désactivant tout ce qui aurait pu être activé par erreur : one-shots, layer words, caps word, Clever keys, etc.


### Windows Management layer


## Modifier and layer keys

### Modifier keys

- Les HRM et les layer-tap sont [*timeless*](https://www.reddit.com/r/ErgoMechKeyboards/comments/1q1jo3c/urobs_zmk_timeless_home_row_mods_ported_to_native/) : cette configuration a solutionné définitivement les problèmes qu’un certain nombre d’utilisateurs pouvait rencontrer avec les HRM. Contrairement à ce qu’on pourrait penser, elle utilise plusieurs timers, mais l’utilisateur n’a pas à s’en préoccuper lors de la frappe. Les touches duales doivent juste être combinées avec les touches situées de l’autre côté du clavier pour que tout fonctionne naturellement. Avec les Timeless HRM, vous ne devriez avoir ni de faux positif (une couche ou une modificatrice qui s’active alors qu’elle ne devrait pas), ni de faux négatif (une couche ou une modificatrice qui ne s’active pas alors qu’elle le devrait).
- Possibilité de désactiver les HRM en commentant `KRYPTON_ENABLE_HRM` dans le fichier `config_propergol.h`.
- Possibilité d’affiner le réglage des timers dans ce même fichier.
- Possibilité d’adapter la configuration pour un usage sous macOS en décommentant la ligne `#define KRYPTON_MAC_MODIFIERS` dans le fichier `config_propergol.h`.
- Possibilité de modifier rapidement l’ordre des HRM en éditant le fichier `propergol.h`
- cas particulier du réglage du `E`
- `IDLE_TIME_BEFORE_HOLD_PRIORITY`


### One shot on steroids keys

- La configuration utilise des touches “one shot”. Ces touches se comportent comme des 
- one shot on steroids : timeless, annulables facilement, non soumises à la layer stack, compatibles avec le [Shaka Gesture](https://github.com/lobre/shaka34/blob/main/gesture/README.md)


### Combos

- Les combos peuvent être un game-changer sur les claviers compacts, mais tout le monde n’aime pas. 
- La configuration embarque quelques combos (backspace, enter, tab, escape, alt-tab et PANIC), qui utilisent des touches hors de la rangée de repos.
Comme ça, vous pourrez vous faire votre opinion si vous n’avez jamais testé. 
- Si l’utilisation des combos vous parait naturelle, la configuration peut être optimisée. Ma configuration personnelle en utilise plus, ce qui me permet d’avoir une couche de navigation mieux adaptée à mes besoins.
- La combo alt-tab utilise le [*key repress*](https://docs.qmk.fm/features/combo#customizable-key-repress), ce qui permet de naviguer dans vos fenêtres en lâchant et en réappuyant sur `H` ou `Y` : en appuyant sur les deux touches en même temps on déclenche la combo, qui envoie Alt-tab au système. On peut ensuite se déplacer dans les fenêtres ouvertes en relâchant `H` et en réappuyant dessus. On peut faire la même chose dans l’autre sens avec 'Y'.


## Features

### Layer words
- numword, navword, funword
- facilement modifiables dans `customization.c`

### Caps word, caps list et caps lock

### Select Word, select line

`KRYPTON_THUMB_SHORTCUTS` 

### Clever Keys
Sentence case
