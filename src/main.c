#include <driverlib.h>
#include "header.h"

int main(void)
{
    // System initialization
    SystemClockInit();

    // User initialization
    MenuInit();

    // Enable global interrupt
    Interrupt_enableMaster();

    while (1)
    {

    }
}
