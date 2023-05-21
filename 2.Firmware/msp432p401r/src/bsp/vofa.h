/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#ifndef VOFA_H
#define VOFA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "common.h"
#include "driver/user_uart.h"

#define CHANNEL_NUM     3
#define VOFA_UART       EUSCI_A0_BASE

extern float vofaData[CHANNEL_NUM];

void VofaSendFrame();

#ifdef __cplusplus
}
#endif

#endif
