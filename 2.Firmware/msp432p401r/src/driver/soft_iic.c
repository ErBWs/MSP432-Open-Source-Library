/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 *
 * @note    Modified from SeekFree OpenSource Library
 */

#include "soft_iic.h"

#define SOFT_IIC_SDA_IO_SWITCH          (0)                                     // �Ƿ���Ҫ SDA ���� I/O �л� 0-����Ҫ 1-��Ҫ
#define SoftIIC_Delay(x)  for(uint32_t i = x; i--; )

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC START �ź�
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ���ز���     void
// ʹ��ʾ��     SoftIIC_Start(softIIC);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void SoftIIC_Start (SoftIIC_t *softIIC)
{
    GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                           // SCL �ߵ�ƽ
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA �ߵ�ƽ

    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputLowOnPin(softIIC->sdaPort, softIIC->sdaPin);                                            // SDA ������
    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL ������
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC STOP �ź�
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ���ز���     void
// ʹ��ʾ��     SoftIIC_Stop(softIIC);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void SoftIIC_Stop (SoftIIC_t *softIIC)
{
    GPIO_setOutputLowOnPin(softIIC->sdaPort, softIIC->sdaPin);                                            // SDA �͵�ƽ
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL �͵�ƽ

    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                           // SCL ������
    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA ������
    SoftIIC_Delay(softIIC->delay);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC ���� ACK/NAKC �ź� �ڲ�����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     ack             ACK ��ƽ
// ���ز���     void
// ʹ��ʾ��     SOftIIC_SendAck(softIIC, 1);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void SOftIIC_SendAck (SoftIIC_t *softIIC, uint8_t ack)
{
    Assert(softIIC != NULL);
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL �͵�ƽ

    if(ack)
    {
        GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                       // SDA ����
    }
    else
    {
        GPIO_setOutputLowOnPin(softIIC->sdaPort, softIIC->sdaPin);                                        // SDA ����
    }

    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                           // SCL ����
    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL ����
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA ����
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC ��ȡ ACK/NAKC �ź�
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ���ز���     uint8_t           ACK ״̬
// ʹ��ʾ��     SoftIIC_WaitAck(softIIC);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t SoftIIC_WaitAck (SoftIIC_t *softIIC)
{
    Assert(softIIC != NULL);
    uint8_t temp = 0;
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL �͵�ƽ
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA �ߵ�ƽ �ͷ� SDA
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(softIIC->sdaPort, GPI, GPI_FLOATING_IN);
#endif
    SoftIIC_Delay(softIIC->delay);

    GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                           // SCL �ߵ�ƽ
    SoftIIC_Delay(softIIC->delay);

    if (GPIO_getInputPinValue(softIIC->sdaPort, softIIC->sdaPin))
//    if(gpio_get_level((gpio_pin_enum)softIIC->sdaPort))
    {
        temp = 1;
    }
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL �͵�ƽ
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(softIIC->sdaPort, GPO, GPO_OPEN_DTAIN);
#endif
    SoftIIC_Delay(softIIC->delay);

    return temp;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC ���� 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     data            ����
// ���ز���     uint8_t           ACK ״̬
// ��ע��Ϣ     �ڲ�����
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
        GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                       // SCL ����
        SoftIIC_Delay(softIIC->delay);
        GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                        // SCL ����
    }
    return ((SoftIIC_WaitAck(softIIC) == 1) ? 0 : 1 );
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC ��ȡ 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     ack             ACK �� NACK
// ���ز���     uint8_t           ����
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t SoftIIC_ReadData (SoftIIC_t *softIIC, uint8_t ack)
{
    Assert(softIIC != NULL);
    uint8_t data = 0x00;
    uint8_t temp = 8;
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL �͵�ƽ
    SoftIIC_Delay(softIIC->delay);
    GPIO_setOutputHighOnPin(softIIC->sdaPort, softIIC->sdaPin);                                           // SDA �ߵ�ƽ �ͷ� SDA
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(softIIC->sdaPort, GPI, GPI_FLOATING_IN);
#endif

    while(temp --)
    {
        GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                        // SCL ����
        SoftIIC_Delay(softIIC->delay);
        GPIO_setOutputHighOnPin(softIIC->sclPort, softIIC->sclPin);                                       // SCL ����
        SoftIIC_Delay(softIIC->delay);
        data = ((data << 1) | GPIO_getInputPinValue(softIIC->sdaPort, softIIC->sdaPin));
//        data = ((data << 1) | gpio_get_level((gpio_pin_enum)softIIC->sdaPort));
    }
    GPIO_setOutputLowOnPin(softIIC->sclPort, softIIC->sclPin);                                            // SCL �͵�ƽ
#if SOFT_IIC_SDA_IO_SWITCH
    gpio_set_dir(softIIC->sdaPort, GPO, GPO_OPEN_DTAIN);
#endif
    SoftIIC_Delay(softIIC->delay);
    SOftIIC_SendAck(softIIC, ack);
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� IIC �ӿ�д 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Write8BitRegister(softIIC, 0x01);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿ�д 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Send8BitArray(softIIC, data, 6);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿ���д 16bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Send16BitData(softIIC, 0x0101);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿ�д 16bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Send16BitArray(softIIC, data, 6);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿ��򴫸����Ĵ���д 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Write8BitRegister(softIIC, 0x01, 0x01);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿ��򴫸����Ĵ���д 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Write8BitRegistersArray(softIIC, 0x01, data, 6);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿ��򴫸����Ĵ���д 16bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Write16BitRegister(softIIC, 0x0101, 0x0101);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿ��򴫸����Ĵ���д 16bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Write16BitRegisterArray(softIIC, 0x0101, data, 6);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڶ�ȡ 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ���ز���     uint8_t           ���ض�ȡ�� 8bit ����
// ʹ��ʾ��     SoftIIC_Receive8BitData(softIIC);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ����˵��     *data           Ҫ��ȡ�����ݵĻ�����ָ��
// ����˵��     len             Ҫ��ȡ�����ݳ���
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Receive8BitArray(softIIC, data, 8);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڶ�ȡ 16bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ���ز���     uint16_t          ���ض�ȡ�� 16bit ����
// ʹ��ʾ��     SoftIIC_Receive16BitData(softIIC);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڶ�ȡ 16bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *data           Ҫ��ȡ�����ݵĻ�����ָ��
// ����˵��     len             Ҫ��ȡ�����ݳ���
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Receive16BitArray(softIIC, data, 8);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ���ز���     uint8_t           ���ض�ȡ�� 8bit ����
// ʹ��ʾ��     SoftIIC_Read8BitRegister(softIIC, 0x01);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ����˵��     *data           Ҫ��ȡ�����ݵĻ�����ָ��
// ����˵��     len             Ҫ��ȡ�����ݳ���
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Read8BitRegisterArray(softIIC, 0x01, data, 8);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 16bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ���ز���     uint16_t          ���ض�ȡ�� 16bit ����
// ʹ��ʾ��     SoftIIC_Read16BitRegister(softIIC, 0x0101);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڴӴ������Ĵ�����ȡ 16bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ����˵��     *data           Ҫ��ȡ�����ݵĻ�����ָ��
// ����˵��     len             Ҫ��ȡ�����ݳ���
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Read16BitRegisterArray(softIIC, 0x0101, data, 8);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڴ��� 8bit ���� ��д���ȡ
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *writeData     �������ݴ�Ż�����
// ����˵��     writeLen       ���ͻ���������
// ����˵��     *readData      ��ȡ���ݴ�Ż�����
// ����˵��     readLen        ��ȡ����������
// ���ز���     void            
// ʹ��ʾ��     iic_transfer_8bit_array(IIC_1, addr, data, 64, data, 64);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڴ��� 16bit ���� ��д���ȡ
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     *writeData     �������ݴ�Ż�����
// ����˵��     writeLen       ���ͻ���������
// ����˵��     *readData      ��ȡ���ݴ�Ż�����
// ����˵��     readLen        ��ȡ����������
// ���ز���     void            
// ʹ��ʾ��     iic_transfer_16bit_array(IIC_1, addr, data, 64, data, 64);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿ� SCCB ģʽ�򴫸����Ĵ���д 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_SCCB_WriteRegister(softIIC, 0x01, 0x01);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿ� SCCB ģʽ�Ӵ������Ĵ�����ȡ 8bit ����
// ����˵��     *softIIC   ��� IIC ָ����Ϣ ���Բ��� zf_driver_soft_iic.h ��ĸ�ʽ����
// ����˵��     registerName   �������ļĴ�����ַ
// ���ز���     uint8_t           ���ض�ȡ�� 8bit ����
// ʹ��ʾ��     SoftIIC_SCCB_ReadRegister(softIIC, 0x01);
// ��ע��Ϣ     
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
// �������     ��� IIC �ӿڳ�ʼ�� Ĭ�� MASTER ģʽ ���ṩ SLAVE ģʽ
// ����˵��     *softIIC   ��� IIC ָ����Ϣ��Žṹ���ָ��
// ����˵��     addr            ��� IIC ��ַ ������Ҫע�� ��׼��λ��ַ ���λ���� д��ʱ�����ȷ������
// ����˵��     delay           ��� IIC ��ʱ ����ʱ�Ӹߵ�ƽʱ�� Խ�� IIC ����Խ��
// ����˵��     sclPort         ��� IIC ʱ������ ���� zf_driver_gpio.h �� gpio_pin_enum ö���嶨��
// ����˵��     sdaPort         ��� IIC �������� ���� zf_driver_gpio.h �� gpio_pin_enum ö���嶨��
// ���ز���     void            
// ʹ��ʾ��     SoftIIC_Init(&softIIC, addr, 100, B6, B7);
// ��ע��Ϣ     
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
