# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/qmk)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the Clueboard product line.

## Local changes in this fork

This is a personal fork of [vial-qmk](https://github.com/vial-kb/vial-qmk) with
support for a few specific boards. The upstream documentation below still
applies.

### Elora: PMW3320 trackball and joystick scrolling

The `vial_pmw` keymap (`keyboards/splitkb/elora/keymaps/vial_pmw/`) adds:

* a right-half Elecom EX-G PMW3320 trackball wired into the Myriad socket,
  used for cursor movement at the sensor's maximum resolution;
* left-half Myriad joystick scrolling, using high-resolution scroll with a dead
  zone and acceleration near full deflection;
* a "sniper" mode that halves the trackball CPI while either LT thumb layer is
  held.

The sensor integration lives in `keyboards/splitkb/elora/rev1/myriad.c`. See
the [keymap README](keyboards/splitkb/elora/keymaps/vial_pmw/README.md) for the
pinout and tuning knobs.

### Cheapino: Vial port

`keyboards/cheapino/` adds a Cheapino v2 (RP2040-Zero) port with `default` and
`vial` keymaps (`make cheapino:vial`). Notable pieces:

* a custom matrix driver for the reversible PCB, which scans columns in both
  directions;
* an encoder decoded from matrix intersections, so encoder actions can be
  remapped per layer in Vial while the encoder push button behaves as a normal
  key;
* ghosting correction for the Cheapino's known ghost key combinations;
* Vial configuration with 14 layers, 32 macros and the inner-thumb unlock
  combo, using the same `VIAL_KEYBOARD_UID` as the official Cheapino Vial
  firmware so existing `.vil` layouts keep working;
* a larger wear-levelling backing store so the macro buffer has room.

See [keyboards/cheapino/readme.md](keyboards/cheapino/readme.md) for build and
flash instructions.

### Stable Vial build ID

`util/build_id.py` is pinned to a fixed `BUILD_ID` instead of a random one, so
Vial's EEPROM contents (keymap, tap dances, combos, QMK settings) survive
reflashes. Override it with the `QMK_BUILD_ID` environment variable when the
EEPROM layout changes.

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls).

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
