/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan, XieZhengYang
 */

#include "user_uart.h"


/*!
 * @brief   Printf redirection
 *
 * @note    Do not Modify!
 */
#if defined(__ICCARM__)
#define PUTCHAR_PROTOTYPE int32_t fputc (int32_t ch, FILE *f)
#define GETCHAR_PROTOTYPE int32_t fgetc (FILE *f)
#elif defined(__GNUC__)
#define PUTCHAR_PROTOTYPE int32_t __io_putchar (int32_t ch)
#define GETCHAR_PROTOTYPE int32_t __io_getchar ()
#endif

#if defined(__ICCARM__)
PUTCHAR_PROTOTYPE
{
    uart_write_byte(DEBUG_UART_INDEX, (ch & 0xFF));
    return ch;
}

GETCHAR_PROTOTYPE
{
    return uart_read_byte(DEBUG_UART_INDEX);
}
#else
int fputc (int ch, FILE* f)
{
    UART_transmitData(EUSCI_A0_BASE, (ch & 0xFF));
    return ch;
}

int fgetc(FILE *f)
{
    return UART_receiveData(EUSCI_A0_BASE);
}
#endif

/*!
 * @brief   Init UART module
 *
 * @param   module          Fill this with EUSCI_A0_BASE, EUSCI_A1_BASE, EUSCI_A2_BASE or EUSCI_A3_BASE
 * @param   baudRate        Default is 115200
 *
 * @return  void
 */
void UART_Init(uint32_t module, uint32_t baudRate)
{
#ifdef EUSCI_A_UART_7_BIT_LEN       // If using new version of sdk
    const eUSCI_UART_ConfigV1 uartConfig =
            {
                    EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
                    26,                                            // BRDIV = 26
                    0,                                             // UCxBRF = 0
                    111,                                           // UCxBRS = 111
                    EUSCI_A_UART_NO_PARITY,                        // No Parity
                    EUSCI_A_UART_LSB_FIRST,                        // MSB First
                    EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
                    EUSCI_A_UART_MODE,                             // UART mode
                    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
                    EUSCI_A_UART_8_BIT_LEN                         // 8 bit data length
            };
    ConfigBaudRate((eUSCI_UART_ConfigV1 *) &uartConfig, baudRate); // Set baud rate
#else       // If using old version of sdk
    const eUSCI_UART_Config uartConfig =
        {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,                // SMCLK Clock Source
            26,                                            // BRDIV = 26
            0,                                             // UCxBRF = 0
            111,                                           // UCxBRS = 111
            EUSCI_A_UART_NO_PARITY,                        // No Parity
            EUSCI_A_UART_LSB_FIRST,                        // MSB First
            EUSCI_A_UART_ONE_STOP_BIT,                     // One stop bit
            EUSCI_A_UART_MODE,                             // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
        };
    eusci_calcBaudDividers((eUSCI_UART_Config *)&uartConfig, baudRate); // Set baud rate
#endif

    uint_fast8_t port;
    uint_fast16_t pin;
    uint32_t interruptNum;

    switch (module)
    {
    case EUSCI_A0_BASE:
        port = GPIO_PORT_P1;
        pin = GPIO_PIN2 | GPIO_PIN3;
        break;
    case EUSCI_A1_BASE:
        port = GPIO_PORT_P2;
        pin = GPIO_PIN2 | GPIO_PIN3;
        break;
    case EUSCI_A2_BASE:
        port = GPIO_PORT_P3;
        pin = GPIO_PIN2 | GPIO_PIN3;
        break;
    case EUSCI_A3_BASE:
        port = GPIO_PORT_P9;
        pin = GPIO_PIN6 | GPIO_PIN7;
        break;
    default:
        return;
    }
    GPIO_setAsPeripheralModuleFunctionOutputPin(port, pin, GPIO_PRIMARY_MODULE_FUNCTION);
    UART_initModule(module, &uartConfig);
    UART_enableModule(module);
}


void UART_Send8BitData(uint32_t module, uint8_t data)
{
    UART_transmitData(module, data);
}

void UART_Send8BitArray(uint32_t module, uint8_t *data, uint32_t len)
{
    while (len--)
        UART_Send8BitData(module, *data++);
}