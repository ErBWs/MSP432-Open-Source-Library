/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 *
 * @note    Modified from SeekFree OpenSource Library
 */

#ifndef SOFT_IIC_H
#define SOFT_IIC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <driverlib.h>
#include <stdint.h>
#include <stdio.h>
#include "debug.h"

typedef struct
{
    uint_fast8_t sclPort;
    uint_fast16_t sclPin;
    uint_fast8_t sdaPort;
    uint_fast16_t sdaPin;
    uint8_t addr;                                                   // 器件地址 七位地址模式
    uint32_t delay;                                                  // 模拟 IIC 软延时时长
} SoftIIC_t;

void SoftIIC_Send8BitData(SoftIIC_t *softIIC, uint8_t data);
void SoftIIC_Send8BitArray(SoftIIC_t *softIIC, const uint8_t *data, uint32_t len);

void SoftIIC_Send16BitData(SoftIIC_t *softIIC, uint16_t data);
void SoftIIC_Send16BitArray(SoftIIC_t *softIIC, const uint16_t *data, uint32_t len);

void SoftIIC_Write8BitRegister(SoftIIC_t *softIIC, uint8_t registerName, uint8_t data);
void SoftIIC_Write8BitRegistersArray(SoftIIC_t *softIIC, uint8_t registerName, const uint8_t *data, uint32_t len);

void SoftIIC_Write16BitRegister(SoftIIC_t *softIIC, uint16_t registerName, uint16_t data);
void SoftIIC_Write16BitRegisterArray(SoftIIC_t *softIIC, uint16_t registerName, const uint16_t *data,
                                     uint32_t len);

uint8_t SoftIIC_Receive8BitData(SoftIIC_t *softIIC);
void SoftIIC_Receive8BitArray(SoftIIC_t *softIIC, uint8_t *data, uint32_t len);

uint16_t SoftIIC_Receive16BitData(SoftIIC_t *softIIC);
void SoftIIC_Receive16BitArray(SoftIIC_t *softIIC, uint16_t *data, uint32_t len);

uint8_t SoftIIC_Read8BitRegister(SoftIIC_t *softIIC, uint8_t registerName);
void SoftIIC_Read8BitRegisterArray(SoftIIC_t *softIIC, uint8_t registerName, uint8_t *data, uint32_t len);

uint16_t SoftIIC_Read16BitRegister(SoftIIC_t *softIIC, uint16_t registerName);
void SoftIIC_Read16BitRegisterArray(SoftIIC_t *softIIC, uint16_t registerName, uint16_t *data, uint32_t len);

void SoftIIC_ReadWrite8BitArray(SoftIIC_t *softIIC, const uint8_t *writeData, uint32_t writeLen, uint8_t *readData,
                                uint32_t readLen);
void SoftIIC_ReadWrite16BitArray(SoftIIC_t *softIIC, const uint16_t *writeData, uint32_t writeLen,
                                 uint16_t *readData, uint32_t readLen);

void SoftIIC_SCCB_WriteRegister(SoftIIC_t *softIIC, uint8_t registerName, uint8_t data);
uint8_t SoftIIC_SCCB_ReadRegister(SoftIIC_t *softIIC, uint8_t registerName);

void SoftIIC_Init(SoftIIC_t *softIIC, uint8_t addr, uint32_t delay, uint_fast8_t sclPort, uint_fast16_t sclPin,
                  uint_fast8_t sdaPort, uint_fast16_t sdaPin);

#ifdef __cplusplus
}
#endif

#endif