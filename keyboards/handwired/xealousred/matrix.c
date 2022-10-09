/*
Copyright 2019 Alex Ong

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values


#define MATRIX_ROW_PINS { B0, B1, B2, B3, E6 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4, B5, B6, C6, C7, F7 }

// matrix code
// super fast read_cols code.
static inline matrix_row_t read_cols(void) {
    return (PIND & (1 << 0) ? 0 : (1UL << 0)) |
           (PIND & (1 << 1) ? 0 : (1UL << 1)) |
           (PIND & (1 << 2) ? 0 : (1UL << 2)) |
           (PIND & (1 << 3) ? 0 : (1UL << 3)) |
           (PIND & (1 << 5) ? 0 : (1UL << 4)) |
           (PIND & (1 << 4) ? 0 : (1UL << 5)) |
           (PIND & (1 << 6) ? 0 : (1UL << 6)) |
           (PIND & (1 << 7) ? 0 : (1UL << 7)) |
           (PINB & (1 << 4) ? 0 : (1UL << 8)) |
           (PINB & (1 << 5) ? 0 : (1UL << 9)) |
           (PINB & (1 << 6) ? 0 : (1UL << 10)) |
           (PINC & (1 << 6) ? 0 : (1UL << 11)) |
           (PINC & (1 << 7) ? 0 : (1UL << 12)) |
           (PINF & (1 << 7) ? 0 : (1UL << 13));
}

//done.
static void unselect_rows(void) {
    DDRB &= ~0b00001111;
    PORTB &= ~0b00001111;
    DDRE &= ~0b01000000;
    PORTE &= ~0b01000000;
}

//done.
static void select_row(uint8_t row) {
    switch (row) {
        case 0:
            DDRB |= (1 << 0);
            PORTB &= ~(1 << 0);
            break;
        case 1:
            DDRB |= (1 << 1);
            PORTB &= ~(1 << 1);
            break;
        case 2:
            DDRB |= (1 << 2);
            PORTB &= ~(1 << 2);
            break;
        case 3:
            DDRB |= (1 << 3);
            PORTB &= ~(1 << 3);
            break;
        case 4:
            DDRE |= (1 << 6);
            PORTE &= ~(1 << 6);
            break;
    }
}

static void init_pins(void) {

    DDRB &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6);
    PORTB |= (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6);
    DDRC &= ~(1 << 6 | 1 << 7); //done
    PORTC |= (1 << 6 | 1 << 7); //done
    //todo!
    DDRD &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7);
    PORTD |= (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7);
    DDRE &= ~(1 << 6);
    PORTE |= (1 << 6);
    DDRF &= ~(1 << 7);
    PORTF |= (1 << 7);
}

// Only need to init the pins. Debounce / raw matrix are initialized already for us.
void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
}

// Only need to scan the result into current_matrix, and return changed.
uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        select_row(current_row);
        matrix_output_select_delay();

        matrix_row_t cols = read_cols();
        changed |= (current_matrix[current_row] != cols);
        current_matrix[current_row] = cols;

        unselect_rows();
        //this internally calls matrix_io_delay()
        matrix_output_unselect_delay(current_row, changed);
    }

    return changed;
}
