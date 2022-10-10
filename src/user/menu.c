/*!
 * @file    TestBench.c
 * @author  Baohan
 * @date    2022/10/04
 */


#include "menu.h"

EasyKey_t keyLeft, keyCenter, keyDown, keyRight, keyUp;

/*!
 * @brief       Initialization of 5-direction key
 *
 * @param       None
 * @return      None
 */
void MenuInit(void)
{
    //5_dir switch init
    EasyKeyInit(&keyLeft, GPIO_PORT_P5, GPIO_PIN4, SCANNER_PERIOD);
    EasyKeyInit(&keyCenter, GPIO_PORT_P5, GPIO_PIN5, SCANNER_PERIOD);
    EasyKeyInit(&keyDown, GPIO_PORT_P3, GPIO_PIN7, SCANNER_PERIOD);
    EasyKeyInit(&keyRight, GPIO_PORT_P3, GPIO_PIN5, SCANNER_PERIOD);
    EasyKeyInit(&keyUp, GPIO_PORT_P5, GPIO_PIN1, SCANNER_PERIOD);
}


int32_t angle = 0;
/*!
 * @brief       This function is used for testing other function
 *
 * @param       None
 * @return      None
 *
 * @note        This function should be called below EasyKeyHandler() in timer interrupt
 */
void TestBench()
{
    if (keyCenter.state == press)
    {
        SetPwmDuty(SERVO_PIN, GetServoDuty(0));
    }
    if (keyDown.state == press)
    {
        SetPwmDuty(SERVO_PIN, GetServoDuty(-60));
    }
    if (keyUp.state == press)
    {
        SetPwmDuty(SERVO_PIN, GetServoDuty(60));
    }
    if (keyLeft.state == hold)
    {
        if (angle < 60)
        {
            angle++;
        } else
        {
            angle = 0;
        }
        SetPwmDuty(SERVO_PIN, GetServoDuty(angle));
    }
    if (keyRight.state == hold)
    {
        if (angle > -60)
        {
            angle--;
        } else
        {
            angle = 0;
        }
        SetPwmDuty(SERVO_PIN, GetServoDuty(angle));
    }
}