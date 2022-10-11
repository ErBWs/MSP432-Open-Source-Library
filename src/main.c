#include <driverlib.h>
#include "header.h"


int main(void)
{
    // System initialization
    SystemClockInit();

    // User initialization
    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);
    // EasyKeyInit(&key1, GPIO_PORT_P1, GPIO_PIN1, 10);
    // EnableInterrupt_TimerA3_0();

    uart_init(EUSCI_A0_BASE,115200);
    uart_init(EUSCI_A2_BASE,115200);
    // Enable global interrupt
    Interrupt_enableMaster();

    while (1)
    {
        // GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
        // GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
        UART_transmitData(EUSCI_A2_BASE,1);
        Delay_ms(5000);
        UART_transmitData(EUSCI_A2_BASE,0);
        Delay_ms(1000);
    }
}