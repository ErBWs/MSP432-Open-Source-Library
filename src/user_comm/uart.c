#include "uart.h"

//UART_PutChar( moduleInstance, transmitData);

void UART_PutNChar(uint32_t moduleInstance, uint8_t *transmitData, uint16_t datalength)
{
    for (uint8_t i = 0; i < datalength; i++)
    {
        UART_PutChar( moduleInstance, *transmitData++);
    }
}
