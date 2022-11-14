/*!
 * @file    ctrl.c
 * @author  Baohan
 * @date    2022/10/09
 */

#include "ctrl.h"

// PID parameter array: *Param[5] = {kp, ki, kd, target_value, limitation}
float dirParam[5] = {600, 0, -100, 0, SERVO_DUTY_MAX};       // PD controls for direction, ki should be 0

// PID struct define
PidParam_t dirPid =
        {
                600,
                0,
                -100,
                0,
                SERVO_DUTY_MAX,
                8000,
                800,
                300,
        };


/*!
 * @brief       Motor control init, including encoder init
 *
 * @return      None
 */
void MotorInit(void)
{
    // Servo motor init
    PwmInit(SERVO_PIN, SERVO_FREQ, SERVO_MID);
    // Self check
    SetPwmDuty(SERVO_PIN, GetServoDuty(20));
    Delay_ms(1000);
    SetPwmDuty(SERVO_PIN, GetServoDuty(-20));
    Delay_ms(1000);
    SetPwmDuty(SERVO_PIN, SERVO_MID);

    // Motor and encoder init
    PwmInit(MOTOR_L_PIN, MOTOR_FREQ, 5000);    // Left motor
    PwmInit(MOTOR_R_PIN, MOTOR_FREQ, 5000);    // Right motor

    GPIO_setAsOutputPin(MOTOR_L_DIR_PORT, MOTOR_L_DIR_PIN);     // Left motor direction
    GPIO_setAsOutputPin(MOTOR_R_DIR_PORT, MOTOR_R_DIR_PIN);     // Right motor direction

    // Interrupt init
//    EnableInterrupt_TimerA3_0();     // Use 5ms interrupt
}


/*!
 * @brief       Servo PID control
 *
 * @param       dirErr      Direction error
 * @return      None
 */
void ServoControl(int16_t dirErr)
{
    int32_t servoOut = 0;

    // Servo pid
//    servoOut = PidPosControl(&dirPid, dirParam, dirErr);
    // Servo output
    if (dirErr > 80)
        dirErr = 80;
    if (dirErr < -80)
        dirErr = -80;
    SetPwmDuty(SERVO_PIN, GetServoDuty(dirErr));
}


/*!
 * @brief       Speed PID control
 *
 * @return      None
 */
void SpeedControl(int16_t dirErr)
{
    int32_t leftSpdOut = 5000, rightSpdOut = 5000;

    // PID calculate
    leftSpdOut += (int32_t) dirErr;
    rightSpdOut -= (int32_t) dirErr;

    // Speed output
    if (leftSpdOut >= 0)
    {
        SetPwmDuty(MOTOR_L_PIN, leftSpdOut);
        GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);
    } else
    {
        SetPwmDuty(MOTOR_L_PIN, -leftSpdOut);
        GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN6);
    }
    if (rightSpdOut >= 0)
    {
        SetPwmDuty(MOTOR_R_PIN, rightSpdOut);
        GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN7);
    } else
    {
        SetPwmDuty(MOTOR_R_PIN, -rightSpdOut);
        GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN7);
    }
}