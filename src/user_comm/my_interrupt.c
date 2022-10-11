/*!
 * @file    my_interrupt.c
 * @author  Baohan, XieZhengYang
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
            default:
                return;
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
            default:
                return;
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
    GPIO_clearInterruptFlag(port, pin);
    GPIO_interruptEdgeSelect(port, pin, edge);
    GPIO_enableInterrupt(port, pin);
    Interrupt_enableInterrupt(port + 50);
}


/*!
 * @brief       Init Uart interrupt
 * @param       module          Fill this with EUSCI_A0_BASE, EUSCI_A1_BASE, EUSCI_A2_BASE or EUSCI_A3_BASE
 * @param       baudRate        Default is 115200
 * @param       status          Fill this with EUSCI_A_UART_RECEIVE_INTERRUPT
 *                                             EUSCI_A_UART_TRANSMIT_INTERRUPT
 *                                             EUSCI_A_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT
 *                                             EUSCI_A_UART_BREAKCHAR_INTERRUPT
 * @return      None
 *
 * @note        Note the pin definition: Ax(RXD|TXD)
 *              A0(P1.2|P1.3) A1(P2.2|P2.3) A2(P3.2|P3.3) A3(P9.6|P9.7)
 */
void EnableUartInterrupt(uint32_t module, uint32_t baudRate, uint16_t status)
{
#ifdef EUSCI_A_UART_7_BIT_LEN       // If using new version of sdk
    const eUSCI_UART_ConfigV1 uartConfig =
            {
                    EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
                    26,                                            // BRDIV = 26
                    0,                                             // UCxBRF = 0
                    111,                                           // UCxBRS = 111
                    EUSCI_A_UART_NO_PARITY,                        // No Parity
                    EUSCI_A_UART_LSB_FIRST,                        // MSB First
                    EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
                    EUSCI_A_UART_MODE,                             // UART mode
                    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
                    EUSCI_A_UART_8_BIT_LEN                         // 8 bit data length
            };
    ConfigBaudRate((eUSCI_UART_ConfigV1 *) &uartConfig, baudRate); //配置波特率
#else       // If using old version of sdk
    const eUSCI_UART_Config uartConfig =
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
            26,                                            // BRDIV = 26
            0,                                             // UCxBRF = 0
            111,                                           // UCxBRS = 111
            EUSCI_A_UART_NO_PARITY,                        // No Parity
            EUSCI_A_UART_LSB_FIRST,                        // MSB First
            EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
            EUSCI_A_UART_MODE,                             // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
        };
    eusci_calcBaudDividers((eUSCI_UART_Config *)&uartConfig, baudRate); //配置波特率
#endif

    uint_fast8_t port;
    uint_fast16_t pin;
    uint32_t interruptNum;

    switch (module)
    {
        case EUSCI_A0_BASE:
            port = GPIO_PORT_P1;
            pin = GPIO_PIN2 | GPIO_PIN3;
            break;
        case EUSCI_A1_BASE:
            port = GPIO_PORT_P2;
            pin = GPIO_PIN2 | GPIO_PIN3;
            break;
        case EUSCI_A2_BASE:
            port = GPIO_PORT_P3;
            pin = GPIO_PIN2 | GPIO_PIN3;
            break;
        case EUSCI_A3_BASE:
            port = GPIO_PORT_P9;
            pin = GPIO_PIN6 | GPIO_PIN7;
            break;
        default:
            return;
    }
    GPIO_setAsPeripheralModuleFunctionOutputPin(port, pin, GPIO_PRIMARY_MODULE_FUNCTION);
    UART_initModule(module, &uartConfig);
    UART_enableModule(module);
    UART_enableInterrupt(module, status);
    switch (module)
    {
        case EUSCI_A0_BASE:
            interruptNum = INT_EUSCIA0;
            break;
        case EUSCI_A1_BASE:
            interruptNum = INT_EUSCIA1;
            break;
        case EUSCI_A2_BASE:
            interruptNum = INT_EUSCIA2;
            break;
        case EUSCI_A3_BASE:
            interruptNum = INT_EUSCIA3;
            break;
        default:
            return;
    }
    Interrupt_enableInterrupt(interruptNum);
}