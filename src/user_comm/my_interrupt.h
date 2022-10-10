/*!
 * @file    my_interrupt.h
 * @author  Baohan
 * @date    2022/10/04
 *
  */

#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <driverlib.h>
#include "header.h"

void EnableInterrupt_TimerA0_0();
void EnableInterrupt_TimerA1_0();
void EnableInterrupt_TimerA2_0();
void EnableInterrupt_TimerA3_0();
void uart_init();


#endif
