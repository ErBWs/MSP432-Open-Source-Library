#include <driverlib.h>
#include "header.h"

int main(void)
{
    // System initialization
    SystemClockInit();

    // User initialization
//    MenuInit();
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // Enable global interrupt
    Interrupt_enableMaster();

    while (1)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        Delay_ms(100);
    }
}
