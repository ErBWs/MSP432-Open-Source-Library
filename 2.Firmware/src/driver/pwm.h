/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#ifndef _PWM_H
#define _PWM_H

#include <driverlib.h>
#include "header.h"

#define PWM_DUTY_MAX        10000

typedef enum
{
    TMA0_PWM_CH0_P73    =0x00073,        // 0x 0[TimerA0] 0[CH0] 0[AF0] 7[PORT7] 3[PIN3]
    TMA0_PWM_CH1_P24    =0x01024,        // 0x 0[TimerA0] 1[CH0] 0[AF0] 2[PORT2] 4[PIN4]
    TMA0_PWM_CH2_P25    =0x02025,        // 0x 0[TimerA0] 2[CH0] 0[AF0] 2[PORT2] 5[PIN5]
    TMA0_PWM_CH3_P26    =0x03026,        // 0x 0[TimerA0] 3[CH0] 0[AF0] 2[PORT2] 6[PIN6]
    TMA0_PWM_CH4_P27    =0x04027,        // 0x 0[TimerA0] 4[CH0] 0[AF0] 2[PORT2] 7[PIN7]

    TMA1_PWM_CH0_P80    =0x10180,        // 0x 1[TimerA1] 0[CH0] 1[AF1] 8[PORT8] 0[PIN0]
    TMA1_PWM_CH1_P77    =0x11077,        // 0x 1[TimerA1] 1[CH1] 0[AF0] 7[PORT7] 7[PIN7]
    TMA1_PWM_CH2_P76    =0x12076,        // 0x 1[TimerA1] 2[CH2] 0[AF0] 7[PORT7] 6[PIN6]
    TMA1_PWM_CH3_P75    =0x13075,        // 0x 1[TimerA1] 3[CH3] 0[AF0] 7[PORT7] 5[PIN5]
    TMA1_PWM_CH4_P74    =0x14074,        // 0x 1[TimerA1] 4[CH4] 0[AF0] 7[PORT7] 4[PIN4]

    TMA2_PWM_CH0_P81    =0x20181,        // 0x 2[TimerA0] 0[CH0] 1[AF1] 8[PORT8] 1[PIN1]
    TMA2_PWM_CH1_P56    =0x21056,        // 0x 2[TimerA0] 1[CH1] 0[AF0] 5[PORT5] 6[PIN6]
    TMA2_PWM_CH2_P57    =0x22057,        // 0x 2[TimerA0] 2[CH2] 0[AF0] 5[PORT5] 7[PIN7]
    TMA2_PWM_CH3_P66    =0x23066,        // 0x 2[TimerA0] 3[CH3] 0[AF0] 6[PORT6] 6[PIN6]
    TMA2_PWM_CH4_P67    =0x24067,        // 0x 2[TimerA0] 4[CH4] 0[AF0] [PORT6] 7[PIN7]

    TMA3_PWM_CH0_P104   =0x300A4,        // 0x 3[TimerA0] 0[CH0] 0[AF0] A[PORT10] 4[PIN4]
    TMA3_PWM_CH1_P105   =0x310A5,        // 0x 3[TimerA0] 1[CH1] 0[AF0] A[PORT10] 5[PIN5]
    TMA3_PWM_CH2_P82    =0x32082,        // 0x 3[TimerA0] 2[CH2] 0[AF0] 8[PORT8] 2[PIN2]
    TMA3_PWM_CH3_P92    =0x33092,        // 0x 3[TimerA0] 3[CH3] 0[AF0] 9[PORT9] 2[PIN2]
    TMA3_PWM_CH4_P93    =0x34093,        // 0x 3[TimerA0] 4[CH4] 0[AF0] 9[PORT9] 3[PIN3]
}PwmChannelEnum;

void PwmInit(PwmChannelEnum _pin, const uint32_t freq, const uint_fast16_t duty);
void SetPwmDuty(PwmChannelEnum _pin, const uint_fast16_t duty);

#endif
