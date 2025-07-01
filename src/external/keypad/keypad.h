/**
 * @file keypad.h
 * @brief Keypad (4x4 matrix) interface for Raspberry Pi Pico
 * @author Luis Felipe Patrocinio (https://github.com/luisfpatrocinio/)
 *
 * Provides functions to initialize and scan a 4x4 matrix keypad.
 *
 * @version 0.1
 * @date 07-01-2025
 * @copyright Copyright (c) 2025 Luis Felipe Patrocinio
 * @license This project is released under the MIT License.
 * See LICENSE file for full license text.
 * https://github.com/luisfpatrocinio/bitdog-patroLibs/blob/main/LICENSE
 */
#ifndef KEYPAD_H
#define KEYPAD_H

// Keypad line (row) GPIO pins
#define LINE1 4
#define LINE2 8
#define LINE3 9
#define LINE4 16

// Keypad column GPIO pins
#define COLUMN1 17
#define COLUMN2 18
#define COLUMN3 19
#define COLUMN4 20

extern const uint LINE_PINS[4];
extern const uint COLUMN_PINS[4];

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initializes the GPIO pins for the 4x4 matrix keypad.
 */
void initKeypad(void);

/**
 * @brief Scans the keypad and returns the row and column of the pressed key.
 *
 * @param[out] row Pointer to store the row index (0-3) of the pressed key.
 * @param[out] col Pointer to store the column index (0-3) of the pressed key.
 * @return true if a key is pressed, false otherwise.
 */
bool keypadScan(uint8_t *row, uint8_t *col);

/**
 * @brief Frequency map for each key in the 4x4 matrix (Hz).
 */
extern const int keypad_freq_map[4][4];

#endif // KEYPAD_H