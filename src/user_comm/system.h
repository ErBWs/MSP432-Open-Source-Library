/*!
 * @file    system_lint.h
 * @author  LX, Baohan
 * @date    2022/10/01
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include "driverlib.h"
#include "memory.h"

#define  LFXT    1
#define  HFXT    2
#define  DCO     3
#define  REFO    4

void SystemClockInit();


#endif
