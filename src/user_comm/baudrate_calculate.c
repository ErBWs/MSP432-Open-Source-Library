/*!
 * @file    baudrate_calculate.c
 * @author  TI, m-RNA, XieZhengYang, ErBW_s
 * @date    2022/10/04
 * @note    This code is converted from JavaScript in the online calculator from TI:
 *          https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 *          There are some errors in the origin C code:
 *          3MHz with 9600bps, 3MHz with 192000bps and 48Mhz with 460800bps
 *          I(ErBW_s) modified these errors by setting exceptions
 */

#include "baudrate_calculate.h"

/*
 *  ======== bitPosition ========
 *  return 1(0) if the specified bit position in value is set(clear)
 */
bool bitPosition(uint16_t value, uint16_t position)
{
    if ((value & (1 << position)))
        return 1;
    return 0;
}

/*
 *  ======== ConfigBaudRate ========
 *  computes the eUSCI_UART register settings for a given clock and baud rate
 *
 *      UCOS16:      the oversampling bit (0 or 1)
 *      UCBRx:       the Baud Rate Control Word
 *      UCFx:        the First modulation stage select (UCBRFx)
 *      UCSx:        the Second modulation stage select (UCBRSx)
 *      maxAbsError: the maximum TX error for the register setting above
 *
 *  The first four field names match the names used in Table 18-5,
 *  "Recommended Settings for Typical Crystals and Baudrates", of the
 *  MSP430FR57xx Family User's Guide (SLAU272A).
 */
#ifdef EUSCI_A_UART_7_BIT_LEN
void ConfigBaudRate(eUSCI_UART_ConfigV1 *uart_config, uint32_t baudRate) //固件库v3_40_01_02
#else
void ConfigBaudRate(eUSCI_UART_Config *uart_config, uint32_t baudRate) //固件库v3_21_00_05
#endif
{
    float maxAbsErrorInByte;
    float minAbsError;
    float error;
    uint8_t ii;
    uint16_t jj;
    uint16_t NN;
    uint32_t count;
    uint32_t clockRate;

    if (!uart_config || !baudRate)
    {
        return;
    }

    if (uart_config->selectClockSource == EUSCI_A_UART_CLOCKSOURCE_SMCLK)
        clockRate = MAP_CS_getSMCLK();
    else if (uart_config->selectClockSource == EUSCI_A_UART_CLOCKSOURCE_ACLK)
        clockRate = MAP_CS_getACLK();
    else
    {
        uart_config->selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
        clockRate = MAP_CS_getSMCLK();
    }
    if (baudRate > clockRate)
    {
        return;
    }

    // Exceptions
    if (clockRate == 48000000)
    {
        if (baudRate == 460800)
        {
            uart_config->clockPrescalar = 6;
            uart_config->firstModReg = 8;
            uart_config->secondModReg = 32;
            uart_config->overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
        }
    } else if (clockRate == 3000000)
    {
        if (baudRate == 9600)
        {
            uart_config->clockPrescalar = 19;
            uart_config->firstModReg = 8;
            uart_config->secondModReg = 85;
            uart_config->overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
        } else if (baudRate == 192000)
        {
            uart_config->clockPrescalar = 9;
            uart_config->firstModReg = 12;
            uart_config->secondModReg = 34;
            uart_config->overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
        }
    }

    NN = (uint16_t)((float)clockRate / (float)baudRate);

    minAbsError = 100000;
    for (jj = 0; jj <= 255; jj++)
    {

        maxAbsErrorInByte = 0;
        count = 0;
        for (ii = 0; ii <= 10; ii++)
        {
            count += NN + bitPosition(jj, 7 - (ii % 8));

            //error = (ii + 1) * baudPeriod - count * clockPeriod;
            error = (ii + 1) / (float)baudRate - count / (float)clockRate;

            if (error < 0)
                error = -error;

            if (error > maxAbsErrorInByte)
                maxAbsErrorInByte = error;
        }
        if (maxAbsErrorInByte - minAbsError < -7.3e-12f)
        {
            minAbsError = maxAbsErrorInByte;
            uart_config->secondModReg = jj;
        }
    }

    if (NN < 20)
    {
        uart_config->overSampling = 0;
        uart_config->clockPrescalar = NN;
        uart_config->firstModReg = 0;
    }
    else
    {
        uart_config->overSampling = 1;
        uart_config->clockPrescalar = (uint16_t)((float)NN / 16.0f);
        uart_config->firstModReg = NN - (uart_config->clockPrescalar * 16);
    }
    //return minAbsError * baudRate * 100;
}