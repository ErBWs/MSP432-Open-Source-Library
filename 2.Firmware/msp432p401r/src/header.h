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
#include "bsp/bmi270.h"
#include "bsp/common_font.h"
#include "bsp/icm20602.h"
#include "bsp/imu963ra.h"
#include "bsp/vofa.h"
#include "bsp/zf_ips114.h"

// User code
#include "user/ctrl.h"
#include "EasyUI/easy_key.h"
#include "EasyUI/easy_ui.h"
#include "EasyUI/easy_ui_user_app.h"
#include "EasyUI/user_ips114.h"
#include "user/grayscale_sensor.h"
#include "user/pid.h"


#endif
