// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "quantum.h"
#include "quantum/encoder.h"

#include "cheapino_encoder.h"

#define COL_SHIFTER ((matrix_row_t)1)

#define ENC_ROW  3
#define ENC_A_COL 2
#define ENC_B_COL 4

static bool colABPressed = false;

void encoder_driver_task(void) {
    // The Cheapino has no dedicated encoder pins. The encoder is read through
    // matrix intersections below, so the standard quadrature driver must not
    // also try to handle it.
}

void fix_encoder_action(matrix_row_t current_matrix[]) {
    matrix_row_t encoder_row = current_matrix[ENC_ROW];

    // Check which way the encoder is turned.
    bool colA = encoder_row & (COL_SHIFTER << ENC_A_COL);
    bool colB = encoder_row & (COL_SHIFTER << ENC_B_COL);

    if (colA && colB) {
        colABPressed = true;
    } else if (colA) {
        if (colABPressed) {
            // A+B followed by A means clockwise.
            colABPressed = false;
            encoder_queue_event(0, true);
        }
    } else if (colB) {
        if (colABPressed) {
            // A+B followed by B means counter-clockwise.
            colABPressed = false;
            encoder_queue_event(0, false);
        }
    }

    // Remove the encoder phase bits so they are not seen as normal keypresses.
    // The encoder push button (row 3, col 0) is deliberately left intact so it
    // can be mapped like any other key, including from Vial.
    current_matrix[ENC_ROW] &= ~((COL_SHIFTER << ENC_A_COL) | (COL_SHIFTER << ENC_B_COL));
}
