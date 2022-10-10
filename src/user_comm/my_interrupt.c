/*!
 * @file    my_interrupt.c
 * @author  Baohan
 * @date    2022/10/04
 */

#include "my_interrupt.h"

/*!
 * @brief       Enable TimerA or Timer32 interrupt
 *
 * @param       _timer          See enum in my_interrupt.h
 * @param       period          Trigger period, 1us ~ 65ms for TimerA and 1us ~ 89s for Timer32
 * @return      None
 *
 * @note        User call see the macro in my_interrupt.h
 *              Need period longer than period range please code in handler function in isr.c like this:
 *              if (count < 20)
 *              {
 *                  count++;
 *                  return;
 *              }
 *              count = 0;
 */
void EnableTimerInterrupt(TimerInterrupt_e _timer, uint_fast16_t period)
{
    uint_fast32_t userPeriod;
    uint_fast16_t timerAddress;
    uint_fast16_t timerNumber;
    if (_timer <= 3)
    {
        userPeriod = period - 1;
        if (period > 64999)     // Cannot exceed 65ms
        {
            return;
        }
        switch (_timer)
        {
            case TIM_A0_INT:
                timerAddress = TIMER_A0_BASE;
                timerNumber = INT_TA0_0;
                break;
            case TIM_A1_INT:
                timerAddress = TIMER_A1_BASE;
                timerNumber = INT_TA1_0;
                break;
            case TIM_A2_INT:
                timerAddress = TIMER_A2_BASE;
                timerNumber = INT_TA2_0;
                break;
            case TIM_A3_INT:
                timerAddress = TIMER_A3_BASE;
                timerNumber = INT_TA3_0;
                break;
        }

        Timer_A_UpModeConfig upConfig =
                {
                        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
                        TIMER_A_CLOCKSOURCE_DIVIDER_48,         // Trigger time  = ( ClkDiv + CCR0 + 1 ) / (Clk)
                        userPeriod,
                        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer overflow interrupt
                        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,     // Enable CCR0 interrupt
                        TIMER_A_DO_CLEAR                        // Clear value
                };

        Timer_A_configureUpMode(timerAddress, &upConfig);
        Interrupt_enableSleepOnIsrExit();
        Interrupt_enableInterrupt(timerNumber);
        Timer_A_startCounter(timerAddress, TIMER_A_UP_MODE);
        Timer_A_clearCaptureCompareInterrupt(timerAddress, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    } else if (_timer < 6)
    {
        userPeriod = period * 48 - 1;
        if (period > 88999999)  // Cannot exceed 89s
        {
            return;
        }
        switch (_timer)
        {
            case TIM32_1_INT:
                timerAddress = TIMER32_0_BASE;
                timerNumber = INT_T32_INT1;
                break;
            case TIM32_2_INT:
                timerAddress = TIMER32_1_BASE;
                timerNumber = INT_T32_INT2;
                break;
        }

        Timer32_initModule(timerAddress, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
        Timer32_setCount(timerAddress, userPeriod);
        Timer32_enableInterrupt(timerAddress);
        Timer32_startTimer(timerAddress, false); // Enable continuously triggered interrupt
        Interrupt_enableInterrupt(timerNumber);
    } else
    {
        return;
    }
}


/*!
 * @brief       Enable external interrupt
 *
 * @param       port        See enum in my_interrupt.h
 * @param       pin         Trigger period, 1us ~ 65ms for TimerA and 1us ~ 89s for Timer32
 * @param       edge        fill this param with GPIO_HIGH_TO_LOW_TRANSITION or GPIO_LOW_TO_HIGH_TRANSITION
 * @return      None
 */
void EnableExternalInterrupt(uint_fast8_t port, uint_fast16_t pin, uint_fast8_t edge)
{
    if (pin > 7)
    {
        return;
    }
    GPIO_setAsInputPinWithPullUpResistor(port, pin);
    GPIO_clearInterruptFlag(port,pin);
    GPIO_interruptEdgeSelect(port,pin,edge);
    GPIO_enableInterrupt(port,pin);
    Interrupt_enableInterrupt(port + 50);
}