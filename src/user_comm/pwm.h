/*!
 * @file    pwm.h
 * @author  Baohan
 * @date    2022/10/04
 */

#ifndef _PWM_H
#define _PWM_H

#include <driverlib.h>
#include "header.h"

#define PWM_DUTY_MAX        10000

typedef enum
{
    TMA0_PWM_CH0_P73    =0x0073,        // 0x 0[TimerA0] 0[CH0] 7[PORT7] 3[PIN3]
    TMA0_PWM_CH1_P24    =0x0124,        // 0x 0[TimerA0] 1[CH0] 2[PORT2] 4[PIN4]
    TMA0_PWM_CH2_P25    =0x0225,        // 0x 0[TimerA0] 2[CH0] 2[PORT2] 5[PIN5]
    TMA0_PWM_CH3_P26    =0x0326,        // 0x 0[TimerA0] 3[CH0] 2[PORT2] 6[PIN6]
    TMA0_PWM_CH4_P27    =0x0427,        // 0x 0[TimerA0] 4[CH0] 2[PORT2] 7[PIN7]

    TMA1_PWM_CH0_P80    =0x1080,        // 0x 1[TimerA1] 0[CH0] 8[PORT8] 0[PIN0]
    TMA1_PWM_CH1_P77    =0x1177,        // 0x 1[TimerA1] 1[CH1] 7[PORT7] 7[PIN7]
    TMA1_PWM_CH2_P76    =0x1276,        // 0x 1[TimerA1] 2[CH2] 7[PORT7] 6[PIN6]
    TMA1_PWM_CH3_P75    =0x1375,        // 0x 1[TimerA1] 3[CH3] 7[PORT7] 5[PIN5]
    TMA1_PWM_CH4_P74    =0x1474,        // 0x 1[TimerA1] 4[CH4] 7[PORT7] 4[PIN4]

    TMA2_PWM_CH0_P81    =0x2081,        // 0x 2[TimerA0] 0[CH0] 8[PORT8] 1[PIN1]
    TMA2_PWM_CH1_P56    =0x2156,        // 0x 2[TimerA0] 1[CH1] 5[PORT5] 6[PIN6]
    TMA2_PWM_CH2_P57    =0x2257,        // 0x 2[TimerA0] 2[CH2] 5[PORT5] 7[PIN7]
    TMA2_PWM_CH3_P66    =0x2366,        // 0x 2[TimerA0] 3[CH3] 6[PORT6] 6[PIN6]
    TMA2_PWM_CH4_P67    =0x2467,        // 0x 2[TimerA0] 4[CH4] 6[PORT6] 7[PIN7]

    TMA3_PWM_CH0_P104   =0x30A4,        // 0x 3[TimerA0] 0[CH0] A[PORT10] 4[PIN4]
    TMA3_PWM_CH1_P105   =0x31A5,        // 0x 3[TimerA0] 1[CH1] A[PORT10] 5[PIN5]
    TMA3_PWM_CH2_P82    =0x3282,        // 0x 3[TimerA0] 2[CH2] 8[PORT8] 2[PIN2]
    TMA3_PWM_CH3_P92    =0x3392,        // 0x 3[TimerA0] 3[CH3] 9[PORT9] 2[PIN2]
    TMA3_PWM_CH4_P93    =0x3493,        // 0x 3[TimerA0] 4[CH4] 9[PORT9] 3[PIN3]
}PwmChannel_e;

void PwmInit(PwmChannel_e _pin, const uint32_t freq, const uint_fast16_t duty);
void SetPwmDuty(PwmChannel_e _pin, const uint_fast16_t duty);

#endif
