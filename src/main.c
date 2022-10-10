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
//    EnableInterrupt_TimerA3_0();
    // EnableTimerInterrupt_ms(TIM32_1_INT, 1000);
    // EnableTimerInterrupt_ms(TIM_A3_INT, 10);

    // Enable global interrupt
    Interrupt_enableMaster();

    while (1)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);
        GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN7);
        GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
        Delay_ms(1000);
    }
}