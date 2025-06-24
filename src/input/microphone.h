#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <stdint.h>
#include "hardware/adc.h"

/**
 * @brief Inicializa o hardware do ADC para o microfone.
 */
void initMicrophone();

/**
 * @brief Lê o valor analógico bruto do pino do microfone.
 * @return O valor lido do ADC (0-4095).
 */
uint16_t readMicrophone();

#endif // MICROPHONE_H