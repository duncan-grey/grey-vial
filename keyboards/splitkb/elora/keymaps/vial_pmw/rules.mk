# Copyright 2024 splitkb.com (support@splitkb.com)
# SPDX-License-Identifier: GPL-2.0-or-later

## Vial-specific settings

VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes
ENCODER_MAP_ENABLE = yes
MIDI_ENABLE = yes

## Trackball (PMW3320) on the right half
SRC += drivers/sensors/pmw3320.c
