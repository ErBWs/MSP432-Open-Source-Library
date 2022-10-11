#include <driverlib.h>
#include "header.h"

int main(void)
{
    // System initialization
    SystemClockInit();

    // User initialization
    MenuInit();
    GrayScaleSensorInit();
    MotorInit();
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN1);
    EnableTimerInterrupt_ms(TIM32_1_INT, 1000);
    EnableTimerInterrupt_ms(TIM_A3_INT, 10);
    EnableUartInterrupt(EUSCI_A0_BASE, 115200, EUSCI_A_SPI_RECEIVE_INTERRUPT);

    // Enable global interrupt
    Interrupt_enableMaster();

    while (1)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);
        GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN7);
    }
}