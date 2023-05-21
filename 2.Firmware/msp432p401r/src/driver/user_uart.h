/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan, XieZhengYang
 */

#ifndef user_uart_h
#define user_uart_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <driverlib.h>
#include <stdio.h>
#include <string.h>
#include "baudrate_calculate.h"

void UART_Init(uint32_t module, uint32_t baudRate);

void UART_Send8BitData(uint32_t module, uint8_t data);
void UART_Send8BitArray(uint32_t module, uint8_t *data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif