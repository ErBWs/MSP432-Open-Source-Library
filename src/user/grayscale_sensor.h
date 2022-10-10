/*!
 * @file    grayscale_sensor.h
 * @author  Baohan
 * @date    2022/10/09
 */

#ifndef _GRAYSCALE_SENSOR_H
#define _GRAYSCALE_SENSOR_H

#include <driverlib.h>
#include "header.h"


void GrayScaleSensorInit(void);
void ReadGrayScaleSensor(void);
void GrayScaleSensorHandler(void);

#endif
