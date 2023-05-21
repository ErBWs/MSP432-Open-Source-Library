/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan, XieZhengYang
 */

#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <driverlib.h>
#include "header.h"
#include "baudrate_calculate.h"

typedef enum
{
    // TimerA
    TIM_A0_INT,
    TIM_A1_INT,
    TIM_A2_INT,
    TIM_A3_INT,

    // Timer32
    TIM32_1_INT,
    TIM32_2_INT,
} TimerInterrupt_e;

void EnableTimerInterrupt(TimerInterrupt_e _timer, uint_fast16_t period);
#define EnableTimerInterrupt_us(_timer, period)     EnableTimerInterrupt(_timer, period)
#define EnableTimerInterrupt_ms(_timer, period)     EnableTimerInterrupt(_timer, (period * 1000))

void EnableExternalInterrupt(uint_fast8_t port, uint_fast16_t pin, uint_fast8_t edge);

void EnableUartInterrupt(uint32_t module, uint16_t status);

void SetInterruptPriority(uint32_t module, uint8_t priorityNum);

#endif
