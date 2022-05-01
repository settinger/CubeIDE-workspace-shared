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
  // UART5 is initialized elsewhere by STM32CUBEIDE-generated code
  return CONSOLE_SUCCESS;
}

// TODO: implement this; what to do about transmission errors or backspaces?
consoleError ConsoleIoReceive(uint8_t * buffer, const uint32_t bufferLength, uint32_t * readLength) {
  uint32_t i = 0;
  char ch;

  //HAL_UART_Receive_IT();
  /*
  while (uart_is_readable(uart0))
  {
    ch = uart_getc(uart0);
    uart_putc(uart0, ch); // echo
    buffer[i] = (uint8_t) ch;
    i++;
  }

  *readLength = i;
  return CONSOLE_SUCCESS;
  */

  //HAL_UART_Transmit(&huart5, (uint8_t*) string, strlen((char*) string), 100);
  return CONSOLE_ERROR;
}

consoleError ConsoleIoSend(const char * buffer) {
  HAL_UART_Transmit(&huart5, (uint8_t*)buffer, strlen(buffer), 100);
  return CONSOLE_SUCCESS;
}
