#include <driverlib.h>
#include "header.h"


uint8_t test = 10;

int main(void)
{
    // System initialization
    SystemClockInit();

    // User initialization
    

    // Enable global interrupt
    Interrupt_enableMaster();

    while (1)
    {

    }
}
