/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#include "pwm.h"

/*!
 * @brief       Initialize the Pwm
 *
 * @param       _pin        See the typedef in pwm.h
 * @param       freq        Pwm output frequency
 * @param       duty        Initial duty
 * @return      None
 *
 * @note        You cannot initialize different function on the same Timer
 *              e.g. You cannot initialize TimerA_0 as interrupt and pwm at the same time
 * @example     PWM_Init(TMA0_PWM_CH2_P25, 50, 5000);
 *              Initialize TimerA0, P2_5 as pwm output, with 50 frequency and 5000 initial duty
 */
void PWM_Init(PwmChannel_e _pin, const uint32_t freq, const uint_fast16_t duty)
{
    // GPIO initialization
    uint_fast16_t pin;
    uint_fast8_t af;
    switch (_pin & 0x0000F)
    {
        case 0: pin = GPIO_PIN0;        break;
        case 1: pin = GPIO_PIN1;        break;
        case 2: pin = GPIO_PIN2;        break;
        case 3: pin = GPIO_PIN3;        break;
        case 4: pin = GPIO_PIN4;        break;
        case 5: pin = GPIO_PIN5;        break;
        case 6: pin = GPIO_PIN6;        break;
        case 7: pin = GPIO_PIN7;        break;
    }
    switch ((_pin & 0x00F00) >> 8)
    {
        case 0: af = GPIO_PRIMARY_MODULE_FUNCTION;      break;
        case 1: af = GPIO_SECONDARY_MODULE_FUNCTION;    break;
        case 2: af = GPIO_TERTIARY_MODULE_FUNCTION;     break;
    }
    GPIO_setAsPeripheralModuleFunctionOutputPin((uint_fast8_t)((_pin & 0x000F0) >> 4), pin, af);

    // Get Timer period
    uint32_t ccr0 = 24000000 / freq - 1;
    uint32_t ccr1 = ccr0 * duty / PWM_DUTY_MAX - 1;

    // Get channel
    uint_fast16_t channel;
    switch ((_pin & 0x0F000) >> 12)
    {
        case 0: channel = TIMER_A_CAPTURECOMPARE_REGISTER_0;     break;
        case 1: channel = TIMER_A_CAPTURECOMPARE_REGISTER_1;     break;
        case 2: channel = TIMER_A_CAPTURECOMPARE_REGISTER_2;     break;
        case 3: channel = TIMER_A_CAPTURECOMPARE_REGISTER_3;     break;
        case 4: channel = TIMER_A_CAPTURECOMPARE_REGISTER_4;     break;
    }

    // Setup config array
    const Timer_A_PWMConfig userConfig =
            {
            TIMER_A_CLOCKSOURCE_SMCLK,          // Clock source
            TIMER_A_CLOCKSOURCE_DIVIDER_2,     // Clock divider
            ccr0,                                // The same as ARR in stm32
            channel,                            // Channel
            TIMER_A_OUTPUTMODE_TOGGLE_SET,      // Output mode
            ccr1                                // PWM Duty
            };

    // Output PWM
    uint32_t timerA;
    switch ((_pin & 0xF0000) >> 16)
    {
        case 0: timerA = TIMER_A0_BASE;      break;
        case 1: timerA = TIMER_A1_BASE;      break;
        case 2: timerA = TIMER_A2_BASE;      break;
        case 3: timerA = TIMER_A3_BASE;      break;
    }
    Timer_A_generatePWM(timerA, &userConfig);
}


/*!
 * @brief       Change pwm duty
 *
 * @param       _pin        See the typedef in pwm.h
 * @param       duty        Pwm duty
 * @return      None
 */
void PWM_SetDuty(PwmChannel_e _pin, const uint_fast16_t duty)
{
    Assert(duty <= PWM_DUTY_MAX);       // Cannot output pwm duty that exceed PWM_DUTY_MAX

    // Get timer
    uint32_t timerA;
    switch ((_pin & 0xF0000) >> 16)
    {
        case 0: timerA = TIMER_A0_BASE;      break;
        case 1: timerA = TIMER_A1_BASE;      break;
        case 2: timerA = TIMER_A2_BASE;      break;
        case 3: timerA = TIMER_A3_BASE;      break;
    }

    // Get channel
    uint_fast16_t channel;
    switch ((_pin & 0x0F000) >> 12)
    {
        case 0: channel = TIMER_A_CAPTURECOMPARE_REGISTER_0;     break;
        case 1: channel = TIMER_A_CAPTURECOMPARE_REGISTER_1;     break;
        case 2: channel = TIMER_A_CAPTURECOMPARE_REGISTER_2;     break;
        case 3: channel = TIMER_A_CAPTURECOMPARE_REGISTER_3;     break;
        case 4: channel = TIMER_A_CAPTURECOMPARE_REGISTER_4;     break;
    }

    // Get Timer period
    uint32_t ccr0 = TIMER_A_CMSIS(timerA)->CCR[0];
    uint32_t ccr1 = ccr0 * duty / PWM_DUTY_MAX - 1;

    // Change pwm duty
    TIMER_A_CMSIS(timerA)->CCR[(channel>>1) - 1] = ccr1;
}


/*!
 * @brief       Change pwm frequency
 *
 * @param       _pin        See the typedef in pwm.h
 * @param       duty        Pwm duty
 * @return      None
 */
void PWM_SetFreq(PwmChannel_e _pin, const uint32_t freq)
{
    // Get timer
    uint32_t timerA;
    switch ((_pin & 0xF0000) >> 16)
    {
        case 0: timerA = TIMER_A0_BASE;      break;
        case 1: timerA = TIMER_A1_BASE;      break;
        case 2: timerA = TIMER_A2_BASE;      break;
        case 3: timerA = TIMER_A3_BASE;      break;
    }

    // Get Timer period
    uint32_t ccr0 = 24000000 / freq - 1;

    // Change pwm frequency
    TIMER_A_CMSIS(timerA)->CCR[0] = ccr0;
}