/*!
 * @file    pwm.c
 * @author  Baohan
 * @date    2022/10/04
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
 *              e.g.You cannot initialize TimerA_0 as interrupt and pwm at the same time
 * @example     PwmInit(TMA0_PWM_CH2_P25, 50, 5000);
 *              Initialize TimerA0, P2_5 as PWM, with 50 frequency and 5000 initial duty
 */
void PwmInit(PwmChannel_e _pin, const uint32_t freq, const uint_fast16_t duty)
{
    // GPIO initialization
    uint_fast8_t port;
    uint_fast16_t pin;
    switch ((_pin & 0x00F0) >> 4)
    {
        case 2: port = GPIO_PORT_P2;    break;
        case 5: port = GPIO_PORT_P5;    break;
        case 6: port = GPIO_PORT_P6;    break;
        case 7: port = GPIO_PORT_P7;    break;
        case 8: port = GPIO_PORT_P8;    break;
        case 9: port = GPIO_PORT_P9;    break;
        case 10: port = GPIO_PORT_P10;  break;
    }
    switch (_pin & 0x000F)
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
    GPIO_setAsPeripheralModuleFunctionOutputPin(port, pin, GPIO_PRIMARY_MODULE_FUNCTION);

    // Get Timer period
    uint32_t arr = 1000000 / freq - 1;

    // Get channel
    uint_fast16_t channel;
    switch ((_pin & 0x0F00) >> 8)
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
            TIMER_A_CLOCKSOURCE_DIVIDER_48,     // Clock divider
            arr,                                // The same as ARR in stm32
            channel,                            // Channel
            TIMER_A_OUTPUTMODE_TOGGLE_SET,      // Output mode
            duty                                // PWM Duty
            };

    // Output PWM
    uint32_t timerA;
    switch ((_pin & 0xF000) >> 12)
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
void SetPwmDuty(PwmChannel_e _pin, const uint_fast16_t duty)
{
    if (duty > PWM_DUTY_MAX)
        return;

    // Get timer
    uint32_t timerA;
    switch ((_pin & 0xF000) >> 12)
    {
        case 0: timerA = TIMER_A0_BASE;      break;
        case 1: timerA = TIMER_A1_BASE;      break;
        case 2: timerA = TIMER_A2_BASE;      break;
        case 3: timerA = TIMER_A3_BASE;      break;
    }

    // Get channel
    uint_fast16_t channel;
    switch ((_pin & 0x0F00) >> 8)
    {
        case 0: channel = TIMER_A_CAPTURECOMPARE_REGISTER_0;     break;
        case 1: channel = TIMER_A_CAPTURECOMPARE_REGISTER_1;     break;
        case 2: channel = TIMER_A_CAPTURECOMPARE_REGISTER_2;     break;
        case 3: channel = TIMER_A_CAPTURECOMPARE_REGISTER_3;     break;
        case 4: channel = TIMER_A_CAPTURECOMPARE_REGISTER_4;     break;
    }

    // Change pwm duty
    Timer_A_setCompareValue(timerA, channel,duty);
}