/*!
 * @file    isr.c
 * @author  Baohan
 * @date    2022/10/03
 *
  */

#include "isr.h"

/* Timer IRQ Handler */
void TA0_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);//����ж�״̬
    Timer_A_clearTimer(TIMER_A0_BASE);
    // Write your code here

    // Write your code here
}

void TA1_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);//����ж�״̬
    Timer_A_clearTimer(TIMER_A1_BASE);
    // Write your code here

    // Write your code here
}

void TA2_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);//����ж�״̬
    Timer_A_clearTimer(TIMER_A2_BASE);
    // Write your code here

    // Write your code here
}


void TA3_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);//����ж�״̬
    Timer_A_clearTimer(TIMER_A3_BASE);
    // Write your code here
        
    // Write your code here
}

/* PORT IRQ Handler */
void PORT1_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    switch (status)
    {
        case GPIO_PIN0:
            break;
        case GPIO_PIN1:
            break;
        case GPIO_PIN2:
            break;
        case GPIO_PIN3:
            break;
        case GPIO_PIN4:
            break;
        case GPIO_PIN5:
            break;
        case GPIO_PIN6:
            break;
        case GPIO_PIN7:
            break;
    }
}

void PORT2_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);

    switch (status)
    {
        case GPIO_PIN0:
            break;
        case GPIO_PIN1:
            break;
        case GPIO_PIN2:
            break;
        case GPIO_PIN3:
            break;
        case GPIO_PIN4:
            break;
        case GPIO_PIN5:
            break;
        case GPIO_PIN6:
            break;
        case GPIO_PIN7:
            break;
    }
}

void PORT3_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P3, status);

    switch (status)
    {
        case GPIO_PIN0:
            break;
        case GPIO_PIN1:
            break;
        case GPIO_PIN2:
            break;
        case GPIO_PIN3:
            break;
        case GPIO_PIN4:
            break;
        case GPIO_PIN5:
            break;
        case GPIO_PIN6:
            break;
        case GPIO_PIN7:
            break;
    }
}

void PORT4_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P4, status);

    switch (status)
    {
        case GPIO_PIN0:
            break;
        case GPIO_PIN1:
            break;
        case GPIO_PIN2:
            break;
        case GPIO_PIN3:
            break;
        case GPIO_PIN4:
            break;
        case GPIO_PIN5:
            break;
        case GPIO_PIN6:
            break;
        case GPIO_PIN7:
            break;
    }
}

void PORT5_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    switch (status)
    {
        case GPIO_PIN0:
            break;
        case GPIO_PIN1:
            break;
        case GPIO_PIN2:
            break;
        case GPIO_PIN3:
            break;
        case GPIO_PIN4:
            break;
        case GPIO_PIN5:
            break;
        case GPIO_PIN6:
            break;
        case GPIO_PIN7:
            break;
    }
}

void PORT6_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P6);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P6, status);

    switch (status)
    {
        case GPIO_PIN0:
            break;
        case GPIO_PIN1:
            break;
        case GPIO_PIN2:
            break;
        case GPIO_PIN3:
            break;
        case GPIO_PIN4:
            break;
        case GPIO_PIN5:
            break;
        case GPIO_PIN6:
            break;
        case GPIO_PIN7:
            break;
    }
}

/* Uart IRQ Handler */
void EUSCIA0_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
        
    }
}
void EUSCIA1_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A1_BASE);
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        MAP_UART_clearInterruptFlag(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
    }
}
void EUSCIA2_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);

        if (UART_receiveData(EUSCI_A2_BASE) == 1)
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
        }
        else if (UART_receiveData(EUSCI_A2_BASE) == 0)
        {
            GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
        }
        
    }
}
void EUSCIA3_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A3_BASE);
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        MAP_UART_clearInterruptFlag(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);
    }
}