/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  TI, m-RNA, XieZhengYang, ErBW_s
 */

#ifndef _BAUDRATE_CALCULATE_H
#define _BAUDRATE_CALCULATE_H
#include <driverlib.h>

#ifdef EUSCI_A_UART_7_BIT_LEN
void ConfigBaudRate(eUSCI_UART_ConfigV1 *uart_config, uint32_t baudRate); //固件库v3_40_01_02
#else
void ConfigBaudRate(eUSCI_UART_Config *uart_config, uint32_t baudRate); //固件库v3_21_00_05
#endif

#endif
