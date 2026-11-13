# Cheapino

![cheapino](https://raw.githubusercontent.com/tompi/cheapino/master/doc/images/cheapino_case.webp)

An affordable split 36-key keyboard with an RP2040-Zero, a reversible PCB and
a single encoder. This port targets **Cheapino v2**. It is based on the
upstream hardware at <https://github.com/tompi/cheapino>.

* Keyboard Maintainer: [Thomas Haukland](https://github.com/tompi)
* Hardware Supported: Cheapino v2 (RP2040-Zero)
* Hardware Availability: <https://github.com/tompi/cheapino>

## Vial

The `vial` keymap is built with the current Vial-QMK tree, so it includes all
of the recent Vial features:

* Flow Tap
* Quick Tap term
* Chordal Hold
* Caps Word
* Tap dance, combos, key overrides, layer lock and repeat key
* Encoder mapping from the Vial UI
* Tapping term, permissive hold and other QMK settings from the Vial UI

The keyboard UID is the same as the official Cheapino Vial firmware, so an
existing Vial `.vil` layout can be restored after flashing this firmware.

Build and flash:

    make cheapino:vial
    make cheapino:vial:flash

Or build the UF2 and copy it to the RP2040 in bootloader mode:

    make cheapino:vial
    cp cheapino_vial.uf2 /path/to/RPI-RP2/

Put the RP2040-Zero in bootloader mode by holding the BOOTSEL button while
plugging in USB.

### Unlock combo

Hold the two inner thumb keys (matrix positions `6,11` and `2,5`) to unlock
the keyboard in Vial.

## Encoder

The encoder is wired through matrix intersections rather than dedicated
encoder pins. Rotating it and pressing it are both mapped through QMK, so the
encoder actions can be remapped per layer in Vial.

## Bootloader

Enter the bootloader in three ways:

* **Bootmagic reset**: Hold the top-left key while plugging in the keyboard.
* **Physical reset button**: Briefly press the reset button on the RP2040-Zero.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`, if one is assigned.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information.
