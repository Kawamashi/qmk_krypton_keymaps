# QMK Krypton keymap for Propergol

&nbsp;</br>

<p align="center">
  <picture>
    <source
      media="(prefers-color-scheme: dark)"
      srcset="https://github.com/Kawamashi/qmk_krypton_keymaps/blob/main/png/Common/krypton-logo-dark.png">
    <img
      alt="Krypton logo"
      width="200"
      src="https://github.com/Kawamashi/qmk_krypton_keymaps/blob/main/png/Common/krypton-logo-light.png">
  </picture>
</p>

&nbsp;</br>
## Philosophy

[Propergol](https://github.com/Kawamashi/Propergol) is a great layout, but it needs 4 dedicated thumb keys (for `Space`, `E`, `Repeat` and `Alt-Repeat`). [Nordrassil](https://github.com/empressabyss/nordrassil/tree/main) needs 4 as well, [Magic Roll](https://github.com/Brooklyn-Style/Magic_Roll) 3. Cramming such layouts into a 36-keys keyboard can be quite a challenge. Krypton is my take on this issue. 

I don’t pretend Krypton is perfect, only you can imagine the layout that suits you the best! I designed Krypton as a solid starting point for those who want to try Propergol without spending hours figuring out the keyboard configuration to use with it. I’ve done my best to make it easy for you to customize Krypton and tailor it to your specific needs.

*Tweak it until you love it!*

&nbsp;</br>
## Installation

This repo works as an [External QMK Userspace](https://docs.qmk.fm/newbs_external_userspace), to keep keymaps and shared code outside the main QMK Firmware repository.

1) [Set up QMK](https://docs.qmk.fm/newbs)
2) Clone this repository locally, including its submodules   
   ```
   git clone --recurse-submodules https://github.com/Kawamashi/qmk_krypton_keymaps.git
   ```   
   The submodules contain additional QMK modules used by the keymaps.
   
4) Navigate to the cloned repository and set it as your External Userspace
```
cd qmk_krypton_keymaps
qmk config user.overlay_dir="$(realpath .)"
```
This tells QMK where to find the external keymaps and userspace files. The setting is persistent, so you don't need to repeat this command every time you use QMK.

4) Compile your firmware
   
   You can now compile a keymap just as you would with a regular QMK installation:
   ```   
   qmk compile -kb <keyboard> -km <keymap>
   ```   
   For example, to compile the Krypton Propergol keymap for the Dasbob keyboard:
   ```
   qmk compile -kb dasbob -km propergol
   ```
   The resulting firmware file will be placed in the root of this repository.
