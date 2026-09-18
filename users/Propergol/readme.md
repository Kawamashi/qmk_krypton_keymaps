# QMK Krypton keymap for Propergol

## Philosophy

[Propergol](https://github.com/Kawamashi/Propergol) is a great layout, but it needs 4 dedicated thumb keys (for space, `E`, `Repeat` and `Alt-Repeat`). [Nordrassil](https://github.com/empressabyss/nordrassil/tree/main) needs 4 as well, [Magic Roll](https://github.com/Brooklyn-Style/Magic_Roll) 3. Cramming such layouts into a 36-keys keyboard can be quite a challenge. Krypton is my take on this issue. 

I don’t pretend Krypton is perfect, only you can imagine the layout that suits you the best! I designed Krypton as a solid starting point for those who want to try Propergol without spending hours figuring out the keyboard configuration to use with it. I’ve done my best to make it easy for you to customize Krypton and tailor it to your specific needs.

*Tweak it until you love it!*


## Layers

### Main layer

- shift et one-shot symbols
- HRM optionnels pour les claviers à 6 colonnes
- Layer-tap sous les pouces pour accéder aux couches nav, nombres et fonctions


### 1DK layer

La touche morte est implémentée sous forme de couche. De cette manière : 
- l’utilisateur peut personnaliser la couche 1DK sans avoir besoin de retoucher le driver
- la touche morte peut être annulée par un autre appui sur celle-ci
- les caractères de la couche morte peuvent être enchaînés par un appui prolongé sur la touche 1DK
- Repeat est capable de répéter un caractère de la couche 1DK
- on peut rendre la couche 1DK compatible avec d’autres fonctionnalités de QMK, comme Caps Word, les Clever Keys, etc.
- si l’utilisateur le souhaite, Shift peut s’appliquer au caractère suivant la touche morte. Par exemple, pour taper Ô, on peut faire Shift ★ O.


### Navigation 

couche pour :
- les touches de navigation (flèches, home/end, page up/page down)
- les touches d’édition (backspace (sous les positions de repos de l’index et du pouce), delete, enter, escape, tab, shift tab)
- les raccourcis clavier usuels (cut, copy, paste, undo, redo and select all), accessibles de la main gauche pour pouvoir garder la main sur la souris.
- des macros de navigation mot à mot ainsi que pour effacer un mot entier, des raccourcis pour sélectionner des mots et des lignes
- CAPSWORD, CAPSLIST et CAPSLOCK
- WinMan en one-shot, pour pouvoir gérer les fenêtres en faisant un [Shaka Gesture](https://github.com/lobre/shaka34/blob/main/gesture/README.md).

Couche centrale, donc accessible avec des layer-tap sur les touches de repos des pouces (de la couche principale mais aussi des couches de nombres et de symboles)


### Nombres

- Possibilité de choisir entre 3 couches de nombres différentes, suivant que l’utilisateur veut les nombres disposés en pavé (par défaut) ou en ligne. - Couche accessible par un layer-tap sur une touche de pouce côté gauche, ou bien avec le one-shot de pouce côté droit.

- En plus des chiffres, on trouve NUMWORD. On trouve aussi la touche 1DK (pour pouvoir faire ½, ⅓, etc).
- On trouve aussi Alt-tab/shift alt-tab (ou leurs équivalents Mac) accessible de la main gauche. Ces touches sont implémentées avec [Cyclotab](https://getreuer.info/posts/keyboards/cyclotab/). Il y a également une touche WinNum en one-shot, pour pouvoir gérer les fenêtres en faisant un [Shaka Gesture](https://github.com/lobre/shaka34/blob/main/gesture/README.md).


### Symboles

- Possibilité de choisir entre la couche optimisée de symboles de Propergol ou bien celle d’Ergo‑L.
- Accès aux chiffres grâce à un one-shot, pour pouvoir taper `(0)` ou `[1]` facilement.
- Si Shift est actif quand on accède à la couche de symboles, on accède aux symboles en shift alt-gr à la place.


### Fonctions

- Touches de fonctions et touches média (vol ±, mute, play/pause, previous/next, etc)
- Les touches sont arrangées en fonction de la couche de nombres choisie.
- FUNWORD et PANIC. PANIC permet de remettre le clavier dans sa configuration par défaut, en désactivant tout ce qui aurait pu être activé par erreur : one-shots, layer words, caps word, Clever keys, etc.


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
