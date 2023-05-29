/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 *
 * @note    Modified from SeekFree OpenSource Library
 */

#include "soft_iic.h"

#define SOFT_IIC_SDA_IO_SWITCH          (0)                                     // 是否需要 SDA 进行 I/O 切换 0-不需要 1-需要
#define SoftIIC_Delay(x)  for(uint32_t i = x; i--; )

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC START 信号
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 返回参数     void
// 使用示例     SoftIIC_Start(softIIC);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void SoftIIC_Start (SoftIIC_t *softIIC)
{
    GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                           // SCL 高电平
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA 高电平

    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputLowOnPin(softIIC->sdaPort, softIIC->sdaPin);                                            // SDA 先拉低
    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL 再拉低
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC STOP 信号
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 返回参数     void
// 使用示例     SoftIIC_Stop(softIIC);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void SoftIIC_Stop (SoftIIC_t *softIIC)
{
    GPIO_setOutputLowOnPin(softIIC->sdaPort, softIIC->sdaPin);                                            // SDA 低电平
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL 低电平

    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                           // SCL 先拉高
    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA 再拉高
    SoftIIC_Delay(softIIC->delay);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 发送 ACK/NAKC 信号 内部调用
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     ack             ACK 电平
// 返回参数     void
// 使用示例     SOftIIC_SendAck(softIIC, 1);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void SOftIIC_SendAck (SoftIIC_t *softIIC, uint8_t ack)
{
    Assert(softIIC != NULL);
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL 低电平

    if(ack)
    {
        GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                       // SDA 拉高
    }
    else
    {
        GPIO_setOutputLowOnPin(softIIC->sdaPort, softIIC->sdaPin);                                        // SDA 拉低
    }

    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                           // SCL 拉高
    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL 拉低
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA 拉高
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 获取 ACK/NAKC 信号
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 返回参数     uint8_t           ACK 状态
// 使用示例     SoftIIC_WaitAck(softIIC);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8_t SoftIIC_WaitAck (SoftIIC_t *softIIC)
{
    Assert(softIIC != NULL);
    uint8_t temp = 0;
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL 低电平
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA 高电平 释放 SDA
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(softIIC->sdaPort, GPI, GPI_FLOATING_IN);
#endif
    SoftIIC_Delay(softIIC->delay);

    GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                           // SCL 高电平
    SoftIIC_Delay(softIIC->delay);

    if (GPIO_getInputPinValue(softIIC->sdaPort, softIIC->sdaPin))
//    if(gpio_get_level((gpio_pin_enum)softIIC->sdaPort))
    {
        temp = 1;
    }
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL 低电平
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(softIIC->sdaPort, GPO, GPO_OPEN_DTAIN);
#endif
    SoftIIC_Delay(softIIC->delay);

    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 发送 8bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     data            数据
// 返回参数     uint8_t           ACK 状态
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8_t SoftIIC_SendData (SoftIIC_t *softIIC, const uint8_t data)
{
    Assert(softIIC != NULL);
    uint8_t temp = 0x80;
    while(temp)
    {
        ((data & temp) ? (GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin)) : (GPIO_setOutputLowOnPin(softIIC->sdaPort, softIIC->sdaPin)));
        temp >>= 1;

        SoftIIC_Delay(softIIC->delay);
        GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                       // SCL 拉高
        SoftIIC_Delay(softIIC->delay);
        GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                        // SCL 拉低
    }
    return ((SoftIIC_WaitAck(softIIC) == 1) ? 0 : 1 );
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 读取 8bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     ack             ACK 或 NACK
// 返回参数     uint8_t           数据
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8_t SoftIIC_ReadData (SoftIIC_t *softIIC, uint8_t ack)
{
    Assert(softIIC != NULL);
    uint8_t data = 0x00;
    uint8_t temp = 8;
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL 低电平
    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA 高电平 释放 SDA
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(softIIC->sdaPort, GPI, GPI_FLOATING_IN);
#endif

    while(temp --)
    {
        GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                        // SCL 拉低
        SoftIIC_Delay(softIIC->delay);
        GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                       // SCL 拉高
        SoftIIC_Delay(softIIC->delay);
        data = ((data << 1) | GPIO_getInputPinValue(softIIC->sdaPort, softIIC->sdaPin));
//        data = ((data << 1) | gpio_get_level((gpio_pin_enum)softIIC->sdaPort));
    }
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL 低电平
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(softIIC->sdaPort, GPO, GPO_OPEN_DTAIN);
#endif
    SoftIIC_Delay(softIIC->delay);
    SOftIIC_SendAck(softIIC, ack);
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口写 8bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     SoftIIC_Write8BitRegister(softIIC, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Send8BitData (SoftIIC_t *softIIC, const uint8_t data)
{
    Assert(softIIC != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, data);
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口写 8bit 数组
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     SoftIIC_Send8BitArray(softIIC, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Send8BitArray (SoftIIC_t *softIIC, const uint8_t *data, uint32_t len)
{
    Assert(softIIC != NULL);
    Assert(data != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    while(len --)
    {
        SoftIIC_SendData(softIIC, *data++);
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口器写 16bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     SoftIIC_Send16BitData(softIIC, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Send16BitData (SoftIIC_t *softIIC, const uint16_t data)
{
    Assert(softIIC != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, (uint8_t) ((data & 0xFF00) >> 8));
    SoftIIC_SendData(softIIC, (uint8_t) (data & 0x00FF));
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口写 16bit 数组
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     SoftIIC_Send16BitArray(softIIC, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Send16BitArray (SoftIIC_t *softIIC, const uint16_t *data, uint32_t len)
{
    Assert(softIIC != NULL);
    Assert(data != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    while(len --)
    {
        SoftIIC_SendData(softIIC, (uint8_t) ((*data & 0xFF00) >> 8));
        SoftIIC_SendData(softIIC, (uint8_t) (*data++ & 0x00FF));
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口向传感器寄存器写 8bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     SoftIIC_Write8BitRegister(softIIC, 0x01, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Write8BitRegister (SoftIIC_t *softIIC, const uint8_t registerName, const uint8_t data)
{
    Assert(softIIC != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, registerName);
    SoftIIC_SendData(softIIC, data);
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口向传感器寄存器写 8bit 数组
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     SoftIIC_Write8BitRegistersArray(softIIC, 0x01, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Write8BitRegistersArray (SoftIIC_t *softIIC, const uint8_t registerName, const uint8_t *data, uint32_t len)
{
    Assert(softIIC != NULL);
    Assert(data != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, registerName);
    while(len --)
    {
        SoftIIC_SendData(softIIC, *data++);
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口向传感器寄存器写 16bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     SoftIIC_Write16BitRegister(softIIC, 0x0101, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Write16BitRegister (SoftIIC_t *softIIC, const uint16_t registerName, const uint16_t data)
{
    Assert(softIIC != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, (uint8_t) ((registerName & 0xFF00) >> 8));
    SoftIIC_SendData(softIIC, (uint8_t) (registerName & 0x00FF));
    SoftIIC_SendData(softIIC, (uint8_t) ((data & 0xFF00) >> 8));
    SoftIIC_SendData(softIIC, (uint8_t) (data & 0x00FF));
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口向传感器寄存器写 16bit 数组
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     SoftIIC_Write16BitRegisterArray(softIIC, 0x0101, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Write16BitRegisterArray (SoftIIC_t *softIIC, const uint16_t registerName, const uint16_t *data, uint32_t len)
{
    Assert(softIIC != NULL);
    Assert(data != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, (uint8_t) ((registerName & 0xFF00) >> 8));
    SoftIIC_SendData(softIIC, (uint8_t) (registerName & 0x00FF));
    while(len--)
    {
        SoftIIC_SendData(softIIC, (uint8_t) ((*data & 0xFF00) >> 8));
        SoftIIC_SendData(softIIC, (uint8_t) (*data++ & 0x00FF));
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口读取 8bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 返回参数     uint8_t           返回读取的 8bit 数据
// 使用示例     SoftIIC_Receive8BitData(softIIC);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8_t SoftIIC_Receive8BitData (SoftIIC_t *softIIC)
{
    Assert(softIIC != NULL);
    uint8_t temp = 0;
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    temp = SoftIIC_ReadData(softIIC, 1);
    SoftIIC_Stop(softIIC);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口从传感器寄存器读取 8bit 数组
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 参数说明     *data           要读取的数据的缓冲区指针
// 参数说明     len             要读取的数据长度
// 返回参数     void            
// 使用示例     SoftIIC_Receive8BitArray(softIIC, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Receive8BitArray (SoftIIC_t *softIIC, uint8_t *data, uint32_t len)
{
    Assert(softIIC != NULL);
    Assert(data != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    while(len --)
    {
        *data ++ = SoftIIC_ReadData(softIIC, len == 0);
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口读取 16bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 返回参数     uint16_t          返回读取的 16bit 数据
// 使用示例     SoftIIC_Receive16BitData(softIIC);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16_t SoftIIC_Receive16BitData (SoftIIC_t *softIIC)
{
    Assert(softIIC != NULL);
    uint16_t temp = 0;
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    temp = SoftIIC_ReadData(softIIC, 0);
    temp = ((temp << 8) | SoftIIC_ReadData(softIIC, 1));
    SoftIIC_Stop(softIIC);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口读取 16bit 数组
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     *data           要读取的数据的缓冲区指针
// 参数说明     len             要读取的数据长度
// 返回参数     void            
// 使用示例     SoftIIC_Receive16BitArray(softIIC, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Receive16BitArray (SoftIIC_t *softIIC, uint16_t *data, uint32_t len)
{
    Assert(softIIC != NULL);
    Assert(data != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    while(len --)
    {
        *data = SoftIIC_ReadData(softIIC, 0);
        *data = ((*data << 8) | SoftIIC_ReadData(softIIC, len == 0));
        data ++;
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口从传感器寄存器读取 8bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 返回参数     uint8_t           返回读取的 8bit 数据
// 使用示例     SoftIIC_Read8BitRegister(softIIC, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8_t SoftIIC_Read8BitRegister (SoftIIC_t *softIIC, const uint8_t registerName)
{
    Assert(softIIC != NULL);
    uint8_t temp = 0;
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, registerName);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    temp = SoftIIC_ReadData(softIIC, 1);
    SoftIIC_Stop(softIIC);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口从传感器寄存器读取 8bit 数组
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 参数说明     *data           要读取的数据的缓冲区指针
// 参数说明     len             要读取的数据长度
// 返回参数     void            
// 使用示例     SoftIIC_Read8BitRegisterArray(softIIC, 0x01, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Read8BitRegisterArray (SoftIIC_t *softIIC, const uint8_t registerName, uint8_t *data, uint32_t len)
{
    Assert(softIIC != NULL);
    Assert(data != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, registerName);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    while(len --)
    {
        *data ++ = SoftIIC_ReadData(softIIC, len == 0);
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口从传感器寄存器读取 16bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 返回参数     uint16_t          返回读取的 16bit 数据
// 使用示例     SoftIIC_Read16BitRegister(softIIC, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16_t SoftIIC_Read16BitRegister (SoftIIC_t *softIIC, const uint16_t registerName)
{
    Assert(softIIC != NULL);
    uint16_t temp = 0;
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, (uint8_t) ((registerName & 0xFF00) >> 8));
    SoftIIC_SendData(softIIC, (uint8_t) (registerName & 0x00FF));
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    temp = SoftIIC_ReadData(softIIC, 0);
    temp = ((temp << 8) | SoftIIC_ReadData(softIIC, 1));
    SoftIIC_Stop(softIIC);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口从传感器寄存器读取 16bit 数组
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 参数说明     *data           要读取的数据的缓冲区指针
// 参数说明     len             要读取的数据长度
// 返回参数     void            
// 使用示例     SoftIIC_Read16BitRegisterArray(softIIC, 0x0101, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Read16BitRegisterArray (SoftIIC_t *softIIC, const uint16_t registerName, uint16_t *data, uint32_t len)
{
    Assert(softIIC != NULL);
    Assert(data != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, (uint8_t) ((registerName & 0xFF00) >> 8));
    SoftIIC_SendData(softIIC, (uint8_t) (registerName & 0x00FF));
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    while(len --)
    {
        *data = SoftIIC_ReadData(softIIC, 0);
        *data = ((*data << 8) | SoftIIC_ReadData(softIIC, len == 0));
        data ++;
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口传输 8bit 数组 先写后读取
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     *writeData     发送数据存放缓冲区
// 参数说明     writeLen       发送缓冲区长度
// 参数说明     *readData      读取数据存放缓冲区
// 参数说明     readLen        读取缓冲区长度
// 返回参数     void            
// 使用示例     iic_transfer_8bit_array(IIC_1, addr, data, 64, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_ReadWrite8BitArray (SoftIIC_t *softIIC, const uint8_t *writeData, uint32_t writeLen, uint8_t *readData, uint32_t readLen)
{
    Assert(softIIC != NULL);
    Assert(writeData != NULL);
    Assert(readData != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    while(writeLen --)
    {
        SoftIIC_SendData(softIIC, *writeData++);
    }
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    while(readLen --)
    {
        *readData ++ = SoftIIC_ReadData(softIIC, readLen == 0);
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口传输 16bit 数组 先写后读取
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     *writeData     发送数据存放缓冲区
// 参数说明     writeLen       发送缓冲区长度
// 参数说明     *readData      读取数据存放缓冲区
// 参数说明     readLen        读取缓冲区长度
// 返回参数     void            
// 使用示例     iic_transfer_16bit_array(IIC_1, addr, data, 64, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_ReadWrite16BitArray (SoftIIC_t *softIIC, const uint16_t *writeData, uint32_t writeLen, uint16_t *readData, uint32_t readLen)
{
    Assert(softIIC != NULL);
    Assert(writeData != NULL);
    Assert(readData != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    while(writeLen--)
    {
        SoftIIC_SendData(softIIC, (uint8_t) ((*writeData & 0xFF00) >> 8));
        SoftIIC_SendData(softIIC, (uint8_t) (*writeData++ & 0x00FF));
    }
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    while(readLen --)
    {
        *readData = SoftIIC_ReadData(softIIC, 0);
        *readData = ((*readData << 8) | SoftIIC_ReadData(softIIC, readLen == 0));
        readData ++;
    }
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口 SCCB 模式向传感器寄存器写 8bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     SoftIIC_SCCB_WriteRegister(softIIC, 0x01, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_SCCB_WriteRegister (SoftIIC_t *softIIC, const uint8_t registerName, uint8_t data)
{
    Assert(softIIC != NULL);
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, registerName);
    SoftIIC_SendData(softIIC, data);
    SoftIIC_Stop(softIIC);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口 SCCB 模式从传感器寄存器读取 8bit 数据
// 参数说明     *softIIC   软件 IIC 指定信息 可以参照 zf_driver_soft_iic.h 里的格式看看
// 参数说明     registerName   传感器的寄存器地址
// 返回参数     uint8_t           返回读取的 8bit 数据
// 使用示例     SoftIIC_SCCB_ReadRegister(softIIC, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8_t SoftIIC_SCCB_ReadRegister (SoftIIC_t *softIIC, const uint8_t registerName)
{
    Assert(softIIC != NULL);
    uint8_t temp = 0;
    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1);
    SoftIIC_SendData(softIIC, registerName);
    SoftIIC_Stop(softIIC);

    SoftIIC_Start(softIIC);
    SoftIIC_SendData(softIIC, softIIC->addr << 1 | 0x01);
    temp = SoftIIC_ReadData(softIIC, 1);
    SoftIIC_Stop(softIIC);
    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     软件 IIC 接口初始化 默认 MASTER 模式 不提供 SLAVE 模式
// 参数说明     *softIIC   软件 IIC 指定信息存放结构体的指针
// 参数说明     addr            软件 IIC 地址 这里需要注意 标准七位地址 最高位忽略 写入时请务必确认无误
// 参数说明     delay           软件 IIC 延时 就是时钟高电平时间 越短 IIC 速率越高
// 参数说明     sclPort         软件 IIC 时钟引脚 参照 zf_driver_gpio.h 内 gpio_pin_enum 枚举体定义
// 参数说明     sdaPort         软件 IIC 数据引脚 参照 zf_driver_gpio.h 内 gpio_pin_enum 枚举体定义
// 返回参数     void            
// 使用示例     SoftIIC_Init(&softIIC, addr, 100, B6, B7);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void SoftIIC_Init(SoftIIC_t *softIIC, uint8_t addr, uint32_t delay, uint_fast8_t sclPort, uint_fast16_t sclPin,
                  uint_fast8_t sdaPort, uint_fast16_t sdaPin)
{
    Assert(softIIC != NULL);
    Assert(sclPort != sdaPort || sclPin != sdaPin);
    softIIC->sclPort = sclPort;
    softIIC->sclPin = sclPin;
    softIIC->sdaPort = sdaPort;
    softIIC->sdaPin = sdaPin;
    softIIC->addr = addr;
    softIIC->delay = delay;
    GPIO_setAsOutputPin(sclPort, sclPin);
    GPIO_setAsOutputPin(sdaPort, sdaPin);
}
