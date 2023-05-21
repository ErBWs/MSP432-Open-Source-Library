/*!
 * @file    header.h
 * @author  Baohan
 * @date    2022/10/01
 */

#ifndef _HEADER_H_
#define _HEADER_H_

// User driver
#include "driver/debug.h"
#include "driver/delay.h"
#include "driver/pwm.h"
#include "driver/system.h"
#include "driver/user_intrrupt.h"
#include "driver/user_spi.h"
#include "driver/user_uart.h"

// User peripheral
#include "bsp/vofa.h"

// User code
#include "user/ctrl.h"
#include "user/easy_key.h"
#include "user/grayscale_sensor.h"
#include "user/pid.h"


#endif
