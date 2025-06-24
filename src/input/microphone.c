#include "microphone.h"
#include <stdio.h>

#define MIC_ADC_PIN 28

void initMicrophone()
{
  adc_init();
  adc_gpio_init(MIC_ADC_PIN); // Configura o pino ADC
  adc_select_input(2);        // Seleciona o canal ADC correspondente ao pino
}

uint16_t readMicrophone()
{
  // Aqui, o ADC é configurado para a entrada do microfone (dependendo de como o microfone está conectado)
  uint16_t mic_value = adc_read(); // Exemplo de leitura do ADC
  return mic_value;
}
