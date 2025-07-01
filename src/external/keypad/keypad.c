/**
 * @file keypad.c
 * @brief Implementation of 4x4 matrix keypad interface for Raspberry Pi Pico
 * @author Luis Felipe Patrocinio (https://github.com/luisfpatrocinio/)
 *
 * Handles GPIO initialization and scanning for key presses.
 *
 * @version 0.1
 * @date 07-01-2025
 * @copyright Copyright (c) 2025 Luis Felipe Patrocinio
 * @license This project is released under the MIT License.
 * See LICENSE file for full license text.
 * https://github.com/luisfpatrocinio/bitdog-patroLibs/blob/main/LICENSE
 */
#include "keypad.h"

const int LINE_PINS[4] = {LINE1, LINE2, LINE3, LINE4};
const int COLUMN_PINS[4] = {COLUMN1, COLUMN2, COLUMN3, COLUMN4};

void initKeypad(void)
{
  for (int i = 0; i < 4; i++)
  {
    gpio_init(LINE_PINS[i]);
    gpio_set_dir(LINE_PINS[i], GPIO_OUT);
    gpio_put(LINE_PINS[i], 0);

    gpio_init(COLUMN_PINS[i]);
    gpio_set_dir(COLUMN_PINS[i], GPIO_IN);
    gpio_pull_down(COLUMN_PINS[i]);
  }
}

bool keypadScan(uint8_t *row, uint8_t *col)
{
  // Garante que todas as linhas estão em 0 antes de começar
  for (int r = 0; r < 4; r++)
    gpio_put(LINE_PINS[r], 0);

  for (int r = 0; r < 4; r++)
  {
    gpio_put(LINE_PINS[r], 1); // Ativa a linha atual
    for (int c = 0; c < 4; c++)
    {
      if (gpio_get(COLUMN_PINS[c]))
      {
        if (row)
          *row = r;
        if (col)
          *col = c;
        // Debounce: espera o botão ser solto
        while (gpio_get(COLUMN_PINS[c]))
          tight_loop_contents();
        gpio_put(LINE_PINS[r], 0); // Desativa a linha antes de sair
        return true;
      }
    }
    gpio_put(LINE_PINS[r], 0); // Desativa a linha após varrer as colunas
  }
  return false;
}