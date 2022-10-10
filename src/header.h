/*!
 * @file    header.h
 * @author  Baohan
 * @date    2022/10/01
 */

#ifndef _HEADER_H_
#define _HEADER_H_

#include <driverlib.h>

// User common
#include "user_comm/delay.h"
#include "user_comm/system.h"
#include "user_comm/my_interrupt.h"
#include "user_comm//pwm.h"

// User peripheral
#include "user_peri/easy_key.h"

// User code
#include "user/menu.h"
#include "user/pid.h"
#include "user/grayscale_sensor.h"
#include "user/ctrl.h"

#endif
