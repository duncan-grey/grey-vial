// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Myriad boilerplate
#define MYRIAD_ENABLE

// Elecom EX-G PMW3320 trackball, wired into the right half's Myriad socket:
//   A/SDIO -> IO1 (GP4), F/SCLK -> IO2 (GP5), B/NCS -> MYR (GP9)
// The left half keeps using the Myriad joystick, which keymap.c turns into a
// scroll wheel. The right half reads the trackball for cursor movement.
#define TRACKBALL_ON_RIGHT
#define PMW3320_SDIO_PIN GP4
#define PMW3320_SCLK_PIN GP5
#define PMW3320_CS_PIN GP9
// The sensor's maximum. Run at full resolution and let the host's pointer
// speed/acceleration reduce it if needed.
#define PMW3320_CPI 3500

// Trackball orientation. POINTING_DEVICE_*_RIGHT only affects the right half,
// so these are safe to tune without changing the joystick. Uncomment exactly
// one rotation if the cursor axes are swapped/rotated.
//#define POINTING_DEVICE_ROTATION_90_RIGHT
//#define POINTING_DEVICE_ROTATION_180_RIGHT
//#define POINTING_DEVICE_ROTATION_270_RIGHT
//#define POINTING_DEVICE_INVERT_X_RIGHT
//#define POINTING_DEVICE_INVERT_Y_RIGHT

// Joystick-to-scroll tuning. Values are in high-resolution scroll units
// (1/120 of a wheel notch, see below), so a larger divisor scrolls slower.
// The joystick report is accumulated, so small deflections still scroll
// smoothly. Lower it for faster scrolling, raise it for finer control.
#define MYRIAD_SCROLL_DIVISOR 8

// Dead zone for the joystick, in raw ADC counts (0-512 from centre). Wider
// values ignore more resting offset and noise, at the cost of a longer throw
// before scrolling starts. Raise if the scroll drifts on its own.
#define MYRIAD_SCROLL_DEADZONE 40

// Scroll acceleration. It engages only when an axis is pushed to within
// MYRIAD_SCROLL_BOOST_FROM_PCT percent of full deflection; holding the stick
// there increases the scroll rate from 100% to MYRIAD_SCROLL_BOOST_MAX percent
// over MYRIAD_SCROLL_BOOST_RAMP_MS milliseconds, then plateaus. Moving the
// stick away from the edge resets it, so anything below full tilt scrolls at
// the normal, unaccelerated speed.
#define MYRIAD_SCROLL_BOOST_FROM_PCT 90
#define MYRIAD_SCROLL_BOOST_MAX 200
#define MYRIAD_SCROLL_BOOST_RAMP_MS 1500

// High-resolution scrolling: declare a HID resolution multiplier so the host
// treats every wheel unit as 1/120 of a notch instead of a whole click. This
// is what turns the joystick's scroll from stepped into continuous. Supported
// by Windows and by Linux (kernel >= 5.0 / libinput >= 1.19).
#define POINTING_DEVICE_HIRES_SCROLL_ENABLE
#define POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER 120

// Sniper mode: while one of these layers is held, halve the trackball's
// sensitivity. Layers 2 and 3 are the layers activated by the LT2/LT3 thumb
// keys. Only momentary activation counts (the default layer is ignored), so
// selecting either layer as the base layer does not engage sniper mode.
#define MYRIAD_SNIPER_LAYERS ((1UL << 2) | (1UL << 3))
#define PMW3320_SNIPER_CPI (PMW3320_CPI / 2)

// Scroll direction. These are the plain (non-_RIGHT) defines, so they apply to
// the left-half joystick only; the trackball is unaffected. Uncomment to flip.
//#define POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y

// This unit's product-ID registers do not match the signature that
// pmw3320_check_signature() expects, even though motion reporting works.
// Treat the check as advisory rather than leaving the trackball disabled.
#define PMW3320_SKIP_SIGNATURE_CHECK

/// Vial-specific settings

// Increase the EEPROM size for layout options
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

// Default is 2, needed because keymap has 10 layers
#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// More macro slots (all macros share the remaining EEPROM buffer)
#define DYNAMIC_KEYMAP_MACRO_COUNT 32

// MIDI support (must match "vial": {"midi": "advanced"} in vial.json)
#define MIDI_ADVANCED

#define VIAL_KEYBOARD_UID {0xB3, 0x8D, 0x94, 0xDA, 0xB3, 0xD7, 0xDC, 0x3D}

#define VIAL_UNLOCK_COMBO_ROWS { 3, 9 }
#define VIAL_UNLOCK_COMBO_COLS { 2, 5 }
