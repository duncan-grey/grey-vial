// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral.
#define WS2812_PIO_USE_PIO1
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

// Give the startup LED animation enough executor slots.
#define MAX_DEFERRED_EXECUTORS 32

// The encoder is read through matrix intersections, so this only affects
// the (unused) hardware quadrature driver.
#define ENCODER_RESOLUTION 1
#define ENCODER_MAP_KEY_DELAY 10

// Enlarge the emulated EEPROM so the macro buffer can hold as much as the
// Elora's (32 macros, >600 bytes). RP2040 defaults to 8192 backing / 4096
// logical, which leaves only ~119 bytes for macros once the 14 dynamic
// keymap layers and Vial tables are accounted for.
#define WEAR_LEVELING_BACKING_SIZE 16384
