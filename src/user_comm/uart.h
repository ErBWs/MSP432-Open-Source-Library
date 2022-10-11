#ifndef _UART_H
#define _UART_H
#include <driverlib.h>

#define  UART_PutChar( moduleInstance, transmitData)  UART_transmitData( moduleInstance,  transmitData)

void UART_PutNChar(uint32_t moduleInstance, uint8_t *transmitData, uint16_t datalength);

#endif