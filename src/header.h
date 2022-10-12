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
#include "user_comm/pwm.h"
#include "user_comm/uart.h"
#include "user_comm/shanwai.h"

// User peripheral
#include "user_peri/easy_key.h"
#include "user_peri/IIC_soft.h"
#include "user_peri/ICM20602.h" 

// User code
#include "user/ctrl.h"
#include "user/grayscale_sensor.h"
#include "user/menu.h"
#include "user/pid.h"


#endif
