// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Keep the same UID as the official Cheapino Vial firmware so existing
// .vil layouts continue to load after upgrading.
#define VIAL_KEYBOARD_UID {0x79, 0xED, 0x40, 0xBB, 0x09, 0x8B, 0xC1, 0x9E}
// Unlock combo is the two inner thumb keys.
#define VIAL_UNLOCK_COMBO_ROWS { 6, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 11, 5 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 14

// Match the Elora's macro capacity (32 slots).
#define DYNAMIC_KEYMAP_MACRO_COUNT 32
