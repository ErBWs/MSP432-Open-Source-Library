/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#include "user_spi.h"

/*!
 * @brief       Init SPI as master
 *
 * @param       _mode       Is used to config clockPhase and clockPolarity, please check user_spi.h
 * @param       _csMode     Is used to config spiMode, please check user_spi.h
 * @param       baud        Is used to config desiredSpiClock, better lower than a half of system clock
 * @param       _clkPin     Choose CLK pin, please check user_spi.h
 * @param       _mosiPin    Choose MOSI pin, please check user_spi.h
 * @param       _misoPin    Choose MISO pin, please check user_spi.h
 * @param       _csPin      Choose CS pin, please check user_spi.h
 *
 * @return      None
 */
void SPI_Init(SpiMode_e _mode, SpiCsMode_e _csMode, uint32_t baud, SpiClkPin_e _clkPin, SpiMosiPin_e _mosiPin,
              SpiMisoPin_e _misoPin, SpiCsPin_e _csPin)
{
    uint_fast16_t pin;
    uint_fast8_t af;
    uint_fast16_t phase;
    uint_fast16_t polarity;
    uint_fast16_t mode;
    uint32_t module;
//    uint32_t

    switch (_clkPin & 0x000F)
    {
    case 1:
        pin = GPIO_PIN1;
        break;
    case 3:
        pin = GPIO_PIN3;
        break;
    case 5:
        pin = GPIO_PIN5;
        break;
    }
    GPIO_setAsPeripheralModuleFunctionOutputPin((uint_fast8_t) ((_clkPin & 0x00F0) >> 4), pin,
                                                GPIO_PRIMARY_MODULE_FUNCTION);

    switch (_mosiPin & 0x000F)
    {
    case 2:
        pin = GPIO_PIN2;
        break;
    case 3:
        pin = GPIO_PIN3;
        break;
    case 4:
        pin = GPIO_PIN4;
        break;
    case 6:
        pin = GPIO_PIN6;
        break;
    case 7:
        pin = GPIO_PIN7;
        break;
    }
    switch ((_mosiPin & 0x0F00) >> 8)
    {
    case 0:
        af = GPIO_PRIMARY_MODULE_FUNCTION;
        break;
    case 1:
        af = GPIO_SECONDARY_MODULE_FUNCTION;
        break;
    }
    GPIO_setAsPeripheralModuleFunctionOutputPin((uint_fast8_t) ((_mosiPin & 0x00F0) >> 4), pin, af);

    if (_misoPin != SPI_MISO_NULL)
    {
        switch (_misoPin & 0x000F)
        {
        case 2:
            pin = GPIO_PIN2;
            break;
        case 3:
            pin = GPIO_PIN3;
            break;
        case 5:
            pin = GPIO_PIN5;
            break;
        case 6:
            pin = GPIO_PIN6;
            break;
        case 7:
            pin = GPIO_PIN7;
            break;
        }
        switch ((_misoPin & 0x0F00) >> 8)
        {
        case 0:
            af = GPIO_PRIMARY_MODULE_FUNCTION;
            break;
        case 1:
            af = GPIO_SECONDARY_MODULE_FUNCTION;
            break;
        }
        GPIO_setAsPeripheralModuleFunctionInputPin((uint_fast8_t) ((_misoPin & 0x00F0) >> 4), pin, af);
    }

    switch (_csMode)
    {
    case SPI_CS_MODE0:
        mode = EUSCI_SPI_4PIN_UCxSTE_ACTIVE_HIGH;
        break;
    case SPI_CS_MODE1:
        mode = EUSCI_SPI_4PIN_UCxSTE_ACTIVE_LOW;
        break;
    case SPI_CS_MODE_NULL:
        mode = EUSCI_SPI_3PIN;
        break;
    default:
        break;
    }

    if (_csPin != SPI_CS_NULL)
    {
        switch (_csPin & 0x000F)
        {
        case 0:
            pin = GPIO_PIN0;
            break;
        case 2:
            pin = GPIO_PIN2;
            break;
        case 4:
            pin = GPIO_PIN4;
            break;
        }
        GPIO_setAsPeripheralModuleFunctionOutputPin((uint_fast8_t) ((_csPin & 0x00F0) >> 4), pin,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
    } else
    {
        mode = EUSCI_SPI_3PIN;
    }

    switch (_mode)
    {
    case SPI_MODE0:
        phase = EUSCI_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
        polarity = EUSCI_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
        break;
    case SPI_MODE1:
        phase = EUSCI_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
        polarity = EUSCI_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
        break;
    case SPI_MODE2:
        phase = EUSCI_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
        polarity = EUSCI_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
        break;
    case SPI_MODE3:
        phase = EUSCI_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
        polarity = EUSCI_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
        break;
    default:
        break;
    }

    const eUSCI_SPI_MasterConfig spiMasterConfig =
            {
                    EUSCI_SPI_CLOCKSOURCE_SMCLK,    // SMCLK Clock Source
                    48000000,                       // SMCLK = 48MHZ
                    baud,                           // SPI clock
                    EUSCI_SPI_MSB_FIRST,            // MSB First
                    phase,                          // Phase
                    polarity,                       // Polarity
                    mode                            // SPI Mode
            };
    switch ((_clkPin & 0xF000) >> 12)
    {
    case 0:
        module = EUSCI_A0_BASE;
        break;
    case 1:
        module = EUSCI_A1_BASE;
        break;
    case 2:
        module = EUSCI_A2_BASE;
        break;
    case 3:
        module = EUSCI_A3_BASE;
        break;
    case 4:
        module = EUSCI_B0_BASE;
        break;
    case 5:
        module = EUSCI_B1_BASE;
        break;
    case 6:
        module = EUSCI_B2_BASE;
        break;
    case 7:
        module = EUSCI_B3_BASE;
        break;
    }
    SPI_initMaster(module, &spiMasterConfig);
    SPI_enableModule(module);
}


/*!
 * @brief   Spi data process
 *
 * @param   module          Filled with EUSCI_A0_BASE
                                        EUSCI_A1_BASE
                                        EUSCI_A2_BASE
                                        EUSCI_A3_BASE
                                        EUSCI_B0_BASE
                                        EUSCI_B1_BASE
                                        EUSCI_B2_BASE
                                        EUSCI_B3_BASE
 * @param   data            8 bit data/array or 16 bit data/array
 * @param   registerName    Register name to read or write
 * @param   len             Array length
 */
void SPI_Send8BitData(uint32_t module, uint8_t data)
{
    SPI_transmitData(module, data);
    while (SPI_isBusy(module));
}

void SPI_Send8BitArray(uint32_t module, uint8_t *data, uint32_t len)
{
    while (len--)
    {
        SPI_transmitData(module, *(data++));
        while (SPI_isBusy(module));
    }
}

void SPI_Send16BitData(uint32_t module, uint16_t data)
{
    SPI_transmitData(module, (uint8_t) (data >> 8));
    while (SPI_isBusy(module));
    SPI_transmitData(module, (uint8_t) (data & 0x00ff));
    while (SPI_isBusy(module));
}

void SPI_Send16BitArray(uint32_t module, uint16_t *data, uint32_t len)
{
    while (len--)
    {
        SPI_transmitData(module, (uint8_t) (*data >> 8));
        while (SPI_isBusy(module));
        SPI_transmitData(module, (uint8_t) (*data++ & 0x00ff));
        while (SPI_isBusy(module));
    }
}

void SPI_Write8BitRegister(uint32_t module, uint8_t registerName, uint8_t data)
{
    SPI_transmitData(module, registerName);
    while (SPI_isBusy(module));
    SPI_transmitData(module, data);
    while (SPI_isBusy(module));
}

void SPI_Write8BitRegistersArray(uint32_t module, uint8_t registerName, const uint8_t *data, uint32_t len)
{
    SPI_transmitData(module, registerName);
    while (SPI_isBusy(module));

    while (len--)
    {
        SPI_transmitData(module, *data++);
        while (SPI_isBusy(module));
    }
}

void SPI_Write16BitRegister(uint32_t module, uint16_t registerName, uint16_t data)
{
    SPI_transmitData(module, (uint8_t) (registerName >> 8));
    while (SPI_isBusy(module));
    SPI_transmitData(module, (uint8_t) (registerName & 0x00ff));
    while (SPI_isBusy(module));

    SPI_transmitData(module, (uint8_t) (data >> 8));
    while (SPI_isBusy(module));
    SPI_transmitData(module, (uint8_t) (data & 0x00ff));
    while (SPI_isBusy(module));
}

void SPI_Write16BitRegisterArray(uint32_t module, uint16_t registerName, const uint16_t *data, uint32_t len)
{
    SPI_transmitData(module, (uint8_t) (registerName >> 8));
    while (SPI_isBusy(module));
    SPI_transmitData(module, (uint8_t) (registerName & 0x00ff));
    while (SPI_isBusy(module));

    SPI_transmitData(module, (uint8_t) (*data >> 8));
    while (SPI_isBusy(module));
    SPI_transmitData(module, (uint8_t) (*data++ & 0x00ff));
    while (SPI_isBusy(module));
}

uint8_t SPI_Receive8BitData(uint32_t module)
{
    uint8_t data = 0;

    data = SPI_receiveData(module);
    while (SPI_isBusy(module));

    return data;
}

void SPI_Receive8BitArray(uint32_t module, uint8_t *data, uint32_t len)
{
    while (len--)
    {
        *data++ = SPI_receiveData(module);
        while (SPI_isBusy(module));
    }
}

uint16_t SPI_Receive16BitData(uint32_t module)
{
    uint16_t data = 0;

    data = SPI_receiveData(module);
    while (SPI_isBusy(module));

    data = ((data << 8) | SPI_receiveData(module));
    while (SPI_isBusy(module));

    return data;
}

void SPI_Receive16BitArray(uint32_t module, uint16_t *data, uint32_t len)
{
    while (len--)
    {
        *data = SPI_receiveData(module);
        while (SPI_isBusy(module));

        *data = ((*data << 8) | SPI_receiveData(module));
        data++;
        while (SPI_isBusy(module));
    }
}

uint8_t SPI_Read8BitRegister(uint32_t module, uint8_t registerName)
{
    uint8_t data = 0;

    SPI_transmitData(module, registerName);
    while (SPI_isBusy(module));

    data = SPI_receiveData(module);
    while (SPI_isBusy(module));

    return data;
}

void SPI_Read8BitRegisterArray(uint32_t module, uint8_t registerName, uint8_t *data, uint32_t len)
{
    SPI_transmitData(module, registerName);
    while (SPI_isBusy(module));

    while (len--)
    {
        *data++ = SPI_receiveData(module);
        while (SPI_isBusy(module));
    }
}

uint16_t SPI_Read16BitRegister(uint32_t module, uint16_t registerName)
{
    uint16_t data = 0;

    SPI_transmitData(module, (uint8_t) (registerName >> 8));
    while (SPI_isBusy(module));
    SPI_transmitData(module, (uint8_t) (registerName & 0x00ff));
    while (SPI_isBusy(module));

    data = SPI_receiveData(module);
    while (SPI_isBusy(module));
    data = ((data << 8) | SPI_receiveData(module));
    while (SPI_isBusy(module));
}

void SPI_Read16BitRegisterArray(uint32_t module, uint16_t registerName, uint16_t *data, uint32_t len)
{
    SPI_transmitData(module, (uint8_t) (registerName >> 8));
    while (SPI_isBusy(module));
    SPI_transmitData(module, (uint8_t) (registerName & 0x00ff));
    while (SPI_isBusy(module));

    while (len--)
    {
        *data = SPI_receiveData(module);
        while (SPI_isBusy(module));
        *data = ((*data << 8) | SPI_receiveData(module));
        while (SPI_isBusy(module));
        data++;
    }
}

void SPI_ReadWrite8BitArray(uint32_t module, const uint8_t *writeData, uint8_t *readData, uint32_t len)
{
    while (len--)
    {
        while (SPI_isBusy(module));
        SPI_transmitData(module, *(writeData++));
        if (readData != NULL)
        {
            *readData++ = SPI_receiveData(module);
        }
    }
}

void SPI_ReadWrite16BitArray(uint32_t module, const uint16_t *writeData, uint16_t *readData, uint32_t len)
{
    while (len--)
    {
        while (SPI_isBusy(module));
        SPI_transmitData(module, (uint8_t) (*writeData >> 8));
        if (readData != NULL)
        {
            *readData++ = SPI_receiveData(module);
        }

        while (SPI_isBusy(module));
        SPI_transmitData(module, (uint8_t) (*writeData & 0x00ff));
        if (readData != NULL)
        {
            *readData = SPI_receiveData(module);
        }
        writeData++;
        readData++;
    }
}