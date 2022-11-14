/*!
 * @file    grayscale_sensor.h
 * @author  Baohan
 * @date    2022/10/09
 */

#ifndef _GRAYSCALE_SENSOR_H
#define _GRAYSCALE_SENSOR_H

#include <driverlib.h>
#include "header.h"

extern uint8_t pinLevel[5];

enum TraceType
{
    NORMAL,
    LEFT90,
    RIGHT90,
} traceType;

void GrayScaleSensorInit();
void ReadGrayScaleSensor();
int16_t GetGrayScaleSensorError(int *error);

#endif
