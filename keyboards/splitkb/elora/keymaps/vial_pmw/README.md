# vial_pmw — Elora with a PMW3320 trackball and joystick scrolling

A copy of the stock `vial` keymap with pointing-device support added for one
specific setup:

- **Right half:** an Elecom EX-G PMW3320 trackball wired into the Myriad socket
  drives the cursor.
- **Left half:** the Myriad joystick is repurposed as an always-on scroll wheel.
- **Sniper mode:** holding either of the configured layers halves the trackball
  sensitivity.

Vial itself is unchanged: the keyboard UID and `vial.json` layout are identical
to the `vial` keymap, so a `.vil` exported from either works with both.

## Hardware

The sensor replaces the right half's Myriad module and uses three of its pins:

| PMW3320 | Myriad pin | MCU pin |
| ------- | ---------- | ------- |
| SDIO    | IO1        | GP4     |
| SCLK    | IO2        | GP5     |
| NCS     | MYR        | GP9     |
| VCC/GND | 3V3/GND    | —       |

The sensor is bit-banged (no SPI peripheral), so the pins are defined in
`config.h` as `PMW3320_SDIO_PIN`, `PMW3320_SCLK_PIN`, and `PMW3320_CS_PIN`.

This particular unit does not return the product ID that
`pmw3320_check_signature()` expects (0x3B/0xC4), even though motion reporting
works, so `PMW3320_SKIP_SIGNATURE_CHECK` treats that check as advisory.

## Behaviour

### Trackball (right half)

Read through `rev1/myriad.c` by `pointing_device_driver_get_report()` when the
half is not the left one. It runs at `PMW3320_CPI` (3500, the sensor maximum).

If no sensor is attached, SDIO floats high and every register reads `0xFF`,
which the driver would report as constant motion. The firmware probes the
product ID and its inverse every 250 ms and disables the trackball after four
consecutive all-ones reads. A real sensor returns complementary IDs, so a
working trackball can never be disabled by this check.

### Joystick scrolling (left half)

The joystick report is turned into wheel movement in
`pointing_device_task_combined_user()`. High-resolution scrolling
(`POINTING_DEVICE_HIRES_SCROLL_ENABLE`) makes one wheel unit 1/120 of a notch,
so small deflections scroll continuously instead of in clicks.

The response is linear, with a dead zone that subtracts itself (so scrolling
starts from zero rather than jumping when it engages).

### Scroll acceleration

When an axis is pushed to within `MYRIAD_SCROLL_BOOST_FROM_PCT` of full
deflection, a per-axis boost ramps the scroll rate from 100% to
`MYRIAD_SCROLL_BOOST_MAX` over `MYRIAD_SCROLL_BOOST_RAMP_MS` and then plateaus.
Moving away from the edge resets it immediately, so anything below full tilt
scrolls at the normal speed.

### Sniper mode

While a layer in `MYRIAD_SNIPER_LAYERS` is held momentarily, the trackball CPI
is halved. The default layer is masked out, so selecting one of those layers as
the base layer does not engage it, and a quick layer-tap never activates it.

The CPI change is sent to the right half over the split link via
`pointing_device_set_cpi_on_side()`; `rev1/myriad.c` implements the custom
driver's `get_cpi`/`set_cpi` so the value actually reaches the sensor.

## Tuning

All knobs live in `config.h`:

| Setting | Default | Purpose |
| ------- | ------- | ------- |
| `PMW3320_CPI` | `3500` | Trackball sensitivity (250–3500, 250 steps) |
| `PMW3320_SNIPER_CPI` | `PMW3320_CPI / 2` | Sniper sensitivity |
| `MYRIAD_SNIPER_LAYERS` | layers 2 + 3 | Layers that engage sniper mode |
| `MYRIAD_SCROLL_DIVISOR` | `8` | Base scroll speed (lower = faster) |
| `MYRIAD_SCROLL_DEADZONE` | `40` | Joystick dead zone in raw ADC counts |
| `MYRIAD_SCROLL_BOOST_FROM_PCT` | `90` | How close to full tilt acceleration starts |
| `MYRIAD_SCROLL_BOOST_MAX` | `200` | Plateau, as a percentage of the base rate |
| `MYRIAD_SCROLL_BOOST_RAMP_MS` | `1500` | Time from base rate to plateau |

Uncomment one `POINTING_DEVICE_ROTATION_*_RIGHT` if the cursor axes are
rotated; `POINTING_DEVICE_INVERT_X/Y` affect only the joystick.

## Building and flashing

```sh
make splitkb/elora/rev1:vial_pmw
```

Both halves must run the same firmware. Flash by copying
`splitkb_elora_rev1_vial_pmw.uf2` to the `RPI-RP2` mass-storage device, one half
at a time.

`util/build_id.py` is pinned to a fixed `BUILD_ID`, so Vial's EEPROM contents
survive reflashes. Set `QMK_BUILD_ID` when the EEPROM layout changes and the
stored configuration should be discarded.
