/*!
 * @file    ctrl.h
 * @author  Baohan
 * @date    2022/10/09
 */

#ifndef _CTRL_H
#define _CTRL_H

#include <driverlib.h>
#include "header.h"

#define SERVO_FREQ          50                                  // Servo frequency(50-300)
/*
 * Calculate servo PWM duty from turning angle.
 *
 * Servo often receive a period of 0.5ms to 2.5ms high level pulse,
 * which correspond 0 to 180-degree turning angle.
 *
 * To make calculate easier, I change the angle to [-90, 90],
 * if you want to use [0, 180], change the "1.5" in equation to "0.5".
 *
 * Below is the angle to duty equation,
 * "freq" refers to "PWM frequency"
 *
 *         10000 * (1.5 + x / 90)
 * duty = ------------------------   (-90 <= x <= 90)
 *              1000 / freq
 */
#define GetServoDuty(x)    ((float)(PWM_DUTY_MAX * (2.25 + (float)x / 90.0)) / (1000.0 / (float)SERVO_FREQ))

#define SERVO_MID           GetServoDuty(0)                     // Middle duty of servo motor
#define SERVO_DUTY_MAX      (GetServoDuty(80) - SERVO_MID)      // Maximum turning angle of servo motor
#define SERVO_PIN           TMA0_PWM_CH2_P25                    // Servo pwm output pin

#define MOTOR_FREQ          100                                 // Motor frequency, This motor don't need high frequency
#define MOTOR_L_PIN         TMA0_PWM_CH4_P27                    // Left motor pwm output pin
#define MOTOR_L_DIR_PORT    GPIO_PORT_P6                        // Left motor direction output port
#define MOTOR_L_DIR_PIN     GPIO_PIN6                           // Left motor direction output pin
#define MOTOR_R_PIN         TMA0_PWM_CH3_P26                    // Right motor pwm output pin
#define MOTOR_R_DIR_PORT    GPIO_PORT_P6                        // Right motor direction output port
#define MOTOR_R_DIR_PIN     GPIO_PIN7                           // Right motor direction output pin

extern float spdParam[5];
extern float dirParam[5];

void MotorInit(void);
void ServoControl(int16_t dirErr);
void SpeedControl(void);

#endif
