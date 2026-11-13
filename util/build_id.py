#!/usr/bin/env python3
# Copyright 2026 QMK
# SPDX-License-Identifier: GPL-2.0-or-later
"""Generate the BUILD_ID define used by Vial to validate its EEPROM contents.

Upstream uses a random value, which means every reflash invalidates Vial's
EEPROM and wipes the keymap, tap dances, combos and QMK settings. Using a
stable value keeps that data across firmware updates.

Override with the QMK_BUILD_ID environment variable (must fit in 24 bits) when
the on-device EEPROM layout itself changes, so stale data is discarded.
"""

import os

DEFAULT_BUILD_ID = 0x5A17D0


def main():
    build_id = int(os.environ.get("QMK_BUILD_ID", hex(DEFAULT_BUILD_ID)), 0) & 0xFFFFFF
    print("#define BUILD_ID ((uint32_t)0x{:08X})".format(build_id))


if __name__ == "__main__":
    main()
