#include <driverlib.h>
#include "header.h"

int main(void)
{
    // System initialization
    SystemClockInit();
    SystemPrintfInit();

    // User initialization


    // Enable global interrupt
    Interrupt_enableMaster();

    while (1)
    {

    }
}