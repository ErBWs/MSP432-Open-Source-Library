/*!
 * @file    grayscale_sensor.c
 * @author  Baohan
 * @date    2022/10/09
 */

#include "grayscale_sensor.h"

uint8_t pinLevel[5] = {0, 0, 0, 0, 0};

void GrayScaleSensorInit(void)
{
    GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN0);
    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN7);
    GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN1);
    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN6);
}


void ReadGrayScaleSensor(void)
{
    pinLevel[0] = GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN0);
    pinLevel[1] = GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN7);
    pinLevel[2] = GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN3);
    pinLevel[3] = GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN1);
    pinLevel[4] = GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN6);
}


int16_t GetGrayScaleSensorError(int *error)
{
    ReadGrayScaleSensor();
//    if (pinLevel[0] && pinLevel[1] && pinLevel[2])
//    {
//        traceType = LEFT90;
//    } else if (pinLevel[2] && pinLevel[3] && pinLevel[4])
//    {
//        traceType = RIGHT90;
//    } else
//    {
//        traceType = NORMAL;
//    }
//traceType = NORMAL;
//
//    switch (traceType)
//    {
//        case NORMAL:
//            if (pinLevel[0])
//                error -= 20;
//            if (pinLevel[1])
//                error -= 5;
//            if (pinLevel[3])
//                error += 5;
//            if (pinLevel[4])
//                error += 20;
//            if (pinLevel[2] == 1 && pinLevel[0] == 0 && pinLevel[1] == 0 &&
//                    pinLevel[3] == 0 && pinLevel[4] == 0)
//                error = 0;
//            break;
//        default:
//            break;
//    }
    if (pinLevel[0])
    {
        SetPwmDuty(SERVO_PIN, GetServoDuty(-100));
        return -1800;
    }
    if (pinLevel[1])
    {
        SetPwmDuty(SERVO_PIN, GetServoDuty(-60));
        return -1000;
    }
    if (pinLevel[3])
    {
        SetPwmDuty(SERVO_PIN, GetServoDuty(60));
        return 1000;
    }
    if (pinLevel[4])
    {
        SetPwmDuty(SERVO_PIN, GetServoDuty(100));
        return 1800;
    }
    if (pinLevel[2] == 1 && pinLevel[0] == 0 && pinLevel[1] == 0 &&
        pinLevel[3] == 0 && pinLevel[4] == 0)
    {
        SetPwmDuty(SERVO_PIN, GetServoDuty(0));
        return 0;
    }
}