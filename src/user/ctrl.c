/*!
 * @file    ctrl.c
 * @author  Baohan
 * @date    2022/10/09
 */

#include "ctrl.h"

// PID parameter array: *Param[5] = {kp, ki, kd, target_value, limitation}
float dirParam[5] = {60, 0, -100, 0, SERVO_DUTY_MAX};       // PD controls for direction, ki should be 0

// PID struct define
PID_t dirPid;


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
    SetPwmDuty(SERVO_PIN, GetServoDuty(40));
    Delay_ms(1000);
    SetPwmDuty(SERVO_PIN, GetServoDuty(-40));
    Delay_ms(1000);
    SetPwmDuty(SERVO_PIN, SERVO_MID);

    // Motor and encoder init
    PwmInit(MOTOR_L_PIN, MOTOR_FREQ, 4000);    // Left motor
    PwmInit(MOTOR_R_PIN, MOTOR_FREQ, 4000);    // Right motor

    GPIO_setAsOutputPin(MOTOR_L_DIR_PORT, MOTOR_L_DIR_PIN);     // Left motor direction
    GPIO_setAsOutputPin(MOTOR_R_DIR_PORT, MOTOR_R_DIR_PIN);     // Right motor direction

    // PID init
    PidInit(&dirPid);

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
    int32_t servoOut;

    // Servo pid
    servoOut = PidPosControl(&dirPid, dirParam, dirErr);

    // Servo output
    SetPwmDuty(SERVO_PIN, SERVO_MID + servoOut);
}


/*!
 * @brief       Speed PID control
 *
 * @return      None
 */
void SpeedControl(void)
{
    int32_t leftSpdOut = 0, rightSpdOut = 0;

    // PID calculate
    leftSpdOut += (int32_t)dirPid.out;
    rightSpdOut -= (int32_t)dirPid.out;

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