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

/**
 * @brief Initializes the GPIO pins for the 4x4 matrix keypad.
 */
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

/**
 * @brief Scans the keypad and returns the row and column of the pressed key.
 *
 * @return KeyEvent struct containing the row and column of the pressed key.
 */
KeyEvent keypadScan()
{
  KeyEvent event = {.pressed = false};

  for (int row = 0; row < 4; row++)
  {
    gpio_put(LINE_PINS[row], 1);
    sleep_us(5); // Dá tempo para o sinal estabilizar

    for (int col = 0; col < 4; col++)
    {
      if (gpio_get(COLUMN_PINS[col]))
      {
        event.row = row;
        event.col = col;
        event.pressed = true;

        // Espera soltar
        while (gpio_get(COLUMN_PINS[col]))
        {
          tight_loop_contents();
        }

        gpio_put(LINE_PINS[row], 0);
        return event;
      }
    }

    gpio_put(LINE_PINS[row], 0);
    sleep_us(5); // Dá tempo de descarregar capacitâncias
  }

  return event;
}

// Checar se o teclado está conectado
bool keypadIsConnected()
{
  // Configura as linhas como saída
  for (int i = 0; i < 4; i++)
  {
    gpio_init(LINE_PINS[i]);
    gpio_set_dir(LINE_PINS[i], GPIO_OUT);
  }

  // Configura as colunas como entrada com pull-down
  for (int i = 0; i < 4; i++)
  {
    gpio_init(COLUMN_PINS[i]);
    gpio_set_dir(COLUMN_PINS[i], GPIO_IN);
    gpio_pull_down(COLUMN_PINS[i]);
  }

  // Lógica de teste
  for (int r = 0; r < 4; r++)
  {
    // Ativa uma linha
    gpio_put(LINE_PINS[r], 1);

    // Dá um pequeno tempo para o sinal se estabilizar
    sleep_us(10);

    // Verifica se alguma coluna foi para nível alto
    for (int c = 0; c < 4; c++)
    {
      if (gpio_get(COLUMN_PINS[c]))
      {
        // Se qualquer coluna ler '1', significa que há um caminho.
        // Desativa a linha antes de retornar.
        gpio_put(LINE_PINS[r], 0);
        // Assume-se que o teclado está conectado.
        return true;
      }
    }
    // Desativa a linha antes de testar a próxima
    gpio_put(LINE_PINS[r], 0);
  }

  // Se após testar todas as linhas nenhuma coluna subiu, o teclado está desconectado.
  return false;
}