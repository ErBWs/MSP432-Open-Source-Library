/*!
 * @file    user_spi.c
 * @author  Baohan
 * @date    2022/10/12
 */

#include "user_spi.h"

void SpiInit(SpiModeEnum _mode, uint32_t baud, SpiClkPinEnum _clkPin, SpiMosiPinEnum _mosiPin, SpiMisoPinEnum _misoPin, SpiCsPinEnum _csPin)
{
    const eUSCI_SPI_MasterConfig spiMasterConfig =
            {
                    EUSCI_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source
                    48000000,                                   // SMCLK = DCO = 3MHZ
                    baud,                                    // SPICLK = 500khz
                    EUSCI_SPI_MSB_FIRST,                     // MSB First
                    EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
                    EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, // High polarity
                    EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
            };
}