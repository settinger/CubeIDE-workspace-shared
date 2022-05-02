/*
 * console_io.c
 * A wrapper between raw inputs and console code
 * Ported from Elecia White's code here:
 * https://wokwi.com/projects/324879108372693587
 *
 *  Created on: Apr 27, 2022
 *      Author: Sam
 */

#include "console_io.h"
#include <stdio.h>
#include "string.h"
#include "usart.h"

consoleError ConsoleIoInit(void) {
  // UART5 is initialized elsewhere by STM32CUBEIDE-generated code so this is not necessary
  return CONSOLE_SUCCESS;
}

// What to do about transmission errors or backspaces?
consoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength,
    uint32_t *readLength) {
  uint32_t i = 0;
  uint8_t ch;

  while (huart5.RxState == HAL_UART_STATE_READY && '\r' != ch && '\n' != ch) {
    HAL_UART_Receive(&huart5, (uint8_t*) &ch, 1, HAL_MAX_DELAY); // Next time, try HAL_UART_Receive_IT for non-blocking (interrupt) receiving
    HAL_UART_Transmit(&huart5, (uint8_t*) &ch, 1, HAL_MAX_DELAY); // Display the received character in the console
    buffer[i] = ch;
    i++;
  }

  *readLength = i;

  return CONSOLE_SUCCESS;
}

consoleError ConsoleIoSend(const char *buffer) {
  HAL_UART_Transmit(&huart5, (uint8_t*) buffer, strlen(buffer), 100);
  return CONSOLE_SUCCESS;
}
