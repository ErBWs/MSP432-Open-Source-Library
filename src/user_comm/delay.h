/*!
 * @file    delay.h
 * @author  zf, Baohan
 * @date    2022/05/25
 */

#ifndef _DELAY_H_
#define _DELAY_H_

#include <stdint.h>
#include "driverlib.h"

#define sysClk      48000000          // System clock

void        SystemDelay            (uint32_t time, uint32_t num);

// User call
#define     Delay_ms(time)   SystemDelay(1000000, (time))
#define     Delay_us(time)   SystemDelay((time) * 1000, 1)
#define     Delay_ns(time)   SystemDelay((time), 1)

#endif
