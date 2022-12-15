/*!
 * @file    header.h
 * @author  Baohan
 * @date    2022/10/01
 */

#ifndef _HEADER_H_
#define _HEADER_H_

#include "driverlib.h"

// User driver
#include "driver/delay.h"
#include "driver/system.h"
#include "driver/user_intrrupt.h"
#include "driver/pwm.h"
#include "driver/user_spi.h"
#include "driver/user_uart.h"
#include "driver/shanwai.h"
#include "driver/debug.h"

// User peripheral
#include "bsp/easy_key.h"
#include "bsp/IIC_soft.h"
#include "bsp/ICM20602.h" 
#include "bsp/tft180.h"

// User code
#include "user/ctrl.h"
#include "user/grayscale_sensor.h"
#include "user/menu.h"
#include "user/pid.h"


#endif
