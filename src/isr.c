/*!
 * @file    isr.c
 * @author  Baohan, XieZhengYang
 * @date    2022/10/03
 */

#include "isr.h"

/* Timer IRQ Handler */
void TA0_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);// Clear interrupt status
    // Write your code here

    // Write your code here
}


void TA1_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);// Clear interrupt status
    // Write your code here

    // Write your code here
}


void TA2_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);// Clear interrupt status
    // Write your code here

    // Write your code here
}


void TA3_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);// Clear interrupt status
    // Write your code here
    EasyKeyHandler();
    TestBench();
    ReadGrayScaleSensor();
    GrayScaleSensorHandler();
    // Write your code here
}


void T32_INT1_IRQHandler(void)
{
    Timer32_clearInterruptFlag(TIMER32_0_BASE);     // Clear interrupt status
    // Write your code here

    // Write your code here
}


void T32_INT2_IRQHandler(void)
{
    Timer32_clearInterruptFlag(TIMER32_1_BASE);     // Clear interrupt status
    // Write your code here

    // Write your code here
}


/* PORT IRQ Handler */
void PORT1_IRQHandler(void)
{
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);  // Clear interrupt status

    // -------------Write your code here------------
    if (status & GPIO_PIN0)     // Triggered by P1_0
    {

    }
    if (status & GPIO_PIN1)     // Triggered by P1_1
    {

    }
    if (status & GPIO_PIN2)     // Triggered by P1_2
    {

    }
    if (status & GPIO_PIN3)     // Triggered by P1_3
    {

    }
    if (status & GPIO_PIN4)     // Triggered by P1_4
    {

    }
    if (status & GPIO_PIN5)     // Triggered by P1_5
    {

    }
    if (status & GPIO_PIN6)     // Triggered by P1_6
    {

    }
    if (status & GPIO_PIN7)     // Triggered by P1_7
    {

    }
    // -------------Write your code here------------
}


void PORT2_IRQHandler(void)
{
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status);  // Clear interrupt status

    // -------------Write your code here------------
    if (status & GPIO_PIN0)     // Triggered by P2_0
    {

    }
    if (status & GPIO_PIN1)     // Triggered by P2_1
    {

    }
    if (status & GPIO_PIN2)     // Triggered by P2_2
    {

    }
    if (status & GPIO_PIN3)     // Triggered by P2_3
    {

    }
    if (status & GPIO_PIN4)     // Triggered by P2_4
    {

    }
    if (status & GPIO_PIN5)     // Triggered by P2_5
    {

    }
    if (status & GPIO_PIN6)     // Triggered by P2_6
    {

    }
    if (status & GPIO_PIN7)     // Triggered by P2_7
    {

    }
    // -------------Write your code here------------
}


void PORT3_IRQHandler(void)
{
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);  // Clear interrupt status

    // -------------Write your code here------------
    if (status & GPIO_PIN0)     // Triggered by P3_0
    {

    }
    if (status & GPIO_PIN1)     // Triggered by P3_1
    {

    }
    if (status & GPIO_PIN2)     // Triggered by P3_2
    {

    }
    if (status & GPIO_PIN3)     // Triggered by P3_3
    {

    }
    if (status & GPIO_PIN4)     // Triggered by P3_4
    {

    }
    if (status & GPIO_PIN5)     // Triggered by P3_5
    {

    }
    if (status & GPIO_PIN6)     // Triggered by P3_6
    {

    }
    if (status & GPIO_PIN7)     // Triggered by P3_7
    {

    }
    // -------------Write your code here------------
}


void PORT4_IRQHandler(void)
{
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    GPIO_clearInterruptFlag(GPIO_PORT_P4, status);  // Clear interrupt status

    // -------------Write your code here------------
    if (status & GPIO_PIN0)     // Triggered by P4_0
    {

    }
    if (status & GPIO_PIN1)     // Triggered by P4_1
    {

    }
    if (status & GPIO_PIN2)     // Triggered by P4_2
    {

    }
    if (status & GPIO_PIN3)     // Triggered by P4_3
    {

    }
    if (status & GPIO_PIN4)     // Triggered by P4_4
    {

    }
    if (status & GPIO_PIN5)     // Triggered by P4_5
    {

    }
    if (status & GPIO_PIN6)     // Triggered by P4_6
    {

    }
    if (status & GPIO_PIN7)     // Triggered by P4_7
    {

    }
    // -------------Write your code here------------
}


void PORT5_IRQHandler(void)
{
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);  // Clear interrupt status

    // -------------Write your code here------------
    if (status & GPIO_PIN0)     // Triggered by P5_0
    {

    }
    if (status & GPIO_PIN1)     // Triggered by P5_1
    {

    }
    if (status & GPIO_PIN2)     // Triggered by P5_2
    {

    }
    if (status & GPIO_PIN3)     // Triggered by P5_3
    {

    }
    if (status & GPIO_PIN4)     // Triggered by P5_4
    {

    }
    if (status & GPIO_PIN5)     // Triggered by P5_5
    {

    }
    if (status & GPIO_PIN6)     // Triggered by P5_6
    {

    }
    if (status & GPIO_PIN7)     // Triggered by P5_7
    {

    }
    // -------------Write your code here------------
}


void PORT6_IRQHandler(void)
{
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P6);
    GPIO_clearInterruptFlag(GPIO_PORT_P6, status);  // Clear interrupt status

    // -------------Write your code here------------
    if (status & GPIO_PIN0)     // Triggered by P6_0
    {

    }
    if (status & GPIO_PIN1)     // Triggered by P6_1
    {

    }
    if (status & GPIO_PIN2)     // Triggered by P6_2
    {

    }
    if (status & GPIO_PIN3)     // Triggered by P6_3
    {

    }
    if (status & GPIO_PIN4)     // Triggered by P6_4
    {

    }
    if (status & GPIO_PIN5)     // Triggered by P6_5
    {

    }
    if (status & GPIO_PIN6)     // Triggered by P6_6
    {

    }
    if (status & GPIO_PIN7)     // Triggered by P6_7
    {

    }
    // -------------Write your code here------------
}


/* Uart IRQ Handler */
void EUSCIA0_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
        // Write your code here

        // Write your code here
    }
    if (status & EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG);
        // Write your code here

        // Write your code here
    }
}
void EUSCIA1_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A1_BASE);
    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
        // Write your code here

        // Write your code here
    }
    if (status & EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A1_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG);
        // Write your code here

        // Write your code here
    }
}
void EUSCIA2_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
        // Write your code here

        // Write your code here
    }
    if (status & EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A2_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG);
        // Write your code here

        // Write your code here
    }
}
void EUSCIA3_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A3_BASE);
    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
        // Write your code here

        // Write your code here
    }
    if (status & EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
    {
        UART_clearInterruptFlag(EUSCI_A3_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG);
        // Write your code here

        // Write your code here
    }
}