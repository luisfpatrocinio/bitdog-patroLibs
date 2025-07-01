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

#include "pico/stdlib.h"

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

/**
 * @brief Structure to store the row, column and pressed state of a key.
 *
 * @param row The row of the key.
 * @param col The column of the key.
 * @param pressed The pressed state of the key.
 */
typedef struct
{
  int row;
  int col;
  bool pressed;
} KeyEvent;

/**
 * @brief Initializes the GPIO pins for the 4x4 matrix keypad.
 */
void initKeypad(void);

/**
 * @brief Scans the keypad and returns the row and column of the pressed key.
 *
 * @return KeyEvent struct containing the row and column of the pressed key.
 */
KeyEvent keypadScan(void);

#endif // KEYPAD_H