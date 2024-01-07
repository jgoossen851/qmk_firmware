# Helium

![Helium](https://i.imgur.com/wjOBlxM.png)

A split, 3D-printable row-staggered keyboard.

* Keyboard Maintainer: [Jeremy Goossen](https://github.com/jgoossen851)
* Hardware Supported: Helium 71
* Hardware Availability: None

```bash
# Add the current user to the `dialout` group
sudo usermod -aG dialout $(whoami)
```

Make example for this keyboard (after setting up your build environment):

```bash
qmk compile -kb handwired/helium/71 -km default
```

Flashing example for this keyboard:

```bash
qmk flash -kb handwired/helium/71 -km default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
