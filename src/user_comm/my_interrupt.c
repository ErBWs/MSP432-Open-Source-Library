/*!
 * @file    my_interrupt.c
 * @author  Baohan
 * @date    2022/10/04
 *
  */

#include "my_interrupt.h"
#include "baudrate_calculate.h"
/*!
 * @brief       Enable TimerA0_0 interrupt
 * @param       None
 *
 * @note        Trigger time is 0.05ms, Max Trigger time is 0.065535ms due to uint16
 */
void EnableInterrupt_TimerA0_0()
{
    const Timer_A_UpModeConfig upConfig =
            {
                    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
                    TIMER_A_CLOCKSOURCE_DIVIDER_48,         // Trigger time  = ( ClkDiv + CCR0 + 1 ) / (Clk)
                    49999,
                    TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer overflow interrupt
                    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,    // Enable CCR0 interrupt
                    TIMER_A_DO_CLEAR                        // Clear value
            };

    Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableInterrupt(INT_TA0_0);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}


/*!
 * @brief       Enable TimerA1_0 interrupt
 * @param       None
 *
 * @note        Trigger time is 0.05ms, Max Trigger time is 0.065535ms due to uint16
 */
void EnableInterrupt_TimerA1_0()
{
    const Timer_A_UpModeConfig upConfig =
            {
                    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
                    TIMER_A_CLOCKSOURCE_DIVIDER_48,         // Trigger time  = ( ClkDiv + CCR0 + 1 ) / (Clk)
                    49999,
                    TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer overflow interrupt
                    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,    // Enable CCR0 interrupt
                    TIMER_A_DO_CLEAR                        // Clear value
            };

    Timer_A_configureUpMode(TIMER_A1_BASE, &upConfig);
    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableInterrupt(INT_TA1_0);
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}


/*!
 * @brief       Enable TimerA2_0 interrupt
 * @param       None
 *
 * @note        Trigger time is 0.05ms, Max Trigger time is 0.065535ms due to uint16
 */
void EnableInterrupt_TimerA2_0()
{
    const Timer_A_UpModeConfig upConfig =
            {
                    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
                    TIMER_A_CLOCKSOURCE_DIVIDER_48,         // Trigger time  = ( ClkDiv + CCR0 + 1 ) / (Clk)
                    49999,
                    TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer overflow interrupt
                    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,    // Enable CCR0 interrupt
                    TIMER_A_DO_CLEAR                        // Clear value
            };

    Timer_A_configureUpMode(TIMER_A2_BASE, &upConfig);
    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableInterrupt(INT_TA2_0);
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}


/*!
 * @brief       Enable TimerA3_0 interrupt
 * @param       None
 *
 * @note        Trigger time is 0.05ms, Max Trigger time is 0.065535ms due to uint16
 */
void EnableInterrupt_TimerA3_0()
{
    const Timer_A_UpModeConfig upConfig =
            {
                    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
                    TIMER_A_CLOCKSOURCE_DIVIDER_48,         // Trigger time  = ( ClkDiv + CCR0 + 1 ) / (Clk)
                    49999,
                    TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer overflow interrupt
                    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,    // Enable CCR0 interrupt
                    TIMER_A_DO_CLEAR                        // Clear value
            };

    Timer_A_configureUpMode(TIMER_A3_BASE, &upConfig);
    Interrupt_enableSleepOnIsrExit();
    Interrupt_enableInterrupt(INT_TA3_0);
    Timer_A_startCounter(TIMER_A3_BASE, TIMER_A_UP_MODE);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

/*!
 * @brief       Init Uart interrupt
 * @param       moduleIstance:EUSCI_A0_BASE EUSCI_A1_BASE EUSCI_A2_BASE EUSCI_A3_BASE
 *              baudRate:115200
 * @note        EUSCI_A0_BASE(P1.2|P1.3) EUSCI_A1_BASE(P2.2|P2.3) EUSCI_A2_BASE(P3.2|P3.3) EUSCI_A3_BASE(P9.6|P9.7)
 */

void uart_init(uint32_t moduleInstance,uint32_t baudRate)
{
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
  eusci_calcBaudDividers((eUSCI_UART_ConfigV1 *)&uartConfig, baudRate); //config baudrate
        switch (moduleInstance)
        {
        case EUSCI_A0_BASE:
                MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
                break;
        case EUSCI_A1_BASE:
                MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
                break;
        case EUSCI_A2_BASE:
                MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
                break;
        case EUSCI_A3_BASE:
                MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P9, GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
                break;
        default:
                break;
        }
        MAP_UART_initModule( moduleInstance, &uartConfig);       
        MAP_UART_enableModule( moduleInstance);
        MAP_UART_enableInterrupt(moduleInstance,EUSCI_A_UART_RECEIVE_INTERRUPT);        
        switch (moduleInstance)
        {
        case EUSCI_A0_BASE:
                Interrupt_enableInterrupt(INT_EUSCIA0);
                break;                
        case EUSCI_A1_BASE:
                Interrupt_enableInterrupt(INT_EUSCIA1);
                break;
        case EUSCI_A2_BASE:
                Interrupt_enableInterrupt(INT_EUSCIA2);
                break;
        case EUSCI_A3_BASE:
                Interrupt_enableInterrupt(INT_EUSCIA3);
                break;
        default:
                break;
        }
}