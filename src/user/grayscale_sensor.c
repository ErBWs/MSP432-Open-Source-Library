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


void GrayScaleSensorHandler(void)
{

}