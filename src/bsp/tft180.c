///*********************************************************************************************************************
// * COPYRIGHT NOTICE
// * Copyright (c) 2018,��ɿƼ�
// * All rights reserved.
// * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897  ��Ⱥ��824575535
// *
// * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
// * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
// *
// * @file       		TFT
// * @company	   		�ɶ���ɿƼ����޹�˾
// * @author     		��ɿƼ�(QQ3184284598)
// * @Taobao   		https://seekfree.taobao.com/
// * @date       		2019-11-20
// * @note
// ********************************************************************************************************************/
//
//#include "tft180.h"
//
//
//#define TFT_SCL(x)  gpio_set_2 (TFT180_SCL_PORT,TFT180_SCL_PIN    , x)
//#define TFT_SDA(x)  gpio_set_2 (TFT180_SDA_PORT,TFT180_SDA_PIN    , x)
//#define REST(x)     gpio_set_2 (TFT180_RST_PORT,TFT180_RST_PIN, x)
//#define DC(x)       gpio_set_2 (TFT180_DC_PORT,TFT180_DC_PIN, x)
//#define TFT_CS(x)   gpio_set_2 (TFT180_CS_PORT,TFT180_CS_PIN, x)
//#define BL(x)       gpio_set_2 (TFT180_BL_PORT,    TFT180_BL_PIN, x)
//#define TFT_DC(x)      DC(x);
//
//void gpio_set_2(uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint8_t x)
//{
//
//    if (x)
//    {
//        //GPIO_setAsInputPinWithPullUpResistor(selectedPort,selectedPins);
//        GPIO_setOutputHighOnPin(selectedPort, selectedPins);
//    } else
//    {
//        GPIO_setAsOutputPin(selectedPort, selectedPins);
//        GPIO_setOutputLowOnPin(selectedPort, selectedPins);
//    }
//}
//
//
//void lcd_writeIndex(uint8_t dat)            //д����
//{
//    uint8_t i = 8;
//
//
//    TFT_CS(0);
//    TFT_DC(0);
//    TFT_SCL(0);
//
//    while (i--)
//    {
//        if (dat & 0x80)
//        { TFT_SDA(1); }
//        else
//        { TFT_SDA(0); }
//        TFT_SCL(1);
//
//        TFT_SCL(0);
//        dat <<= 1;
//    }
//    TFT_CS(1);
//}
//
//void lcd_writeData(uint8_t dat)            //д����
//{
//    uint8_t i = 8;
//
//    TFT_CS(0);
//    TFT_DC(1);
//    TFT_SCL(0);
//    while (i--)
//    {
//        if (dat & 0x80)
//        { TFT_SDA(1); }
//        else
//        { TFT_SDA(0); }
//        TFT_SCL(1);
//
//        TFT_SCL(0);
//        dat <<= 1;
//    }
//    TFT_CS(1);
//}
//
//void lcd_writedata_16bit(uint16 dat)    //��Һ����дһ��16λ����
//{
//    uint8_t i = 16;
//    TFT_CS(0);
//    TFT_DC(1);
//    TFT_SCL(0);
//    while (i--)
//    {
//        if (dat & 0x8000)
//        { TFT_SDA(1); }
//        else
//        { TFT_SDA(0); }
//        TFT_SCL(1);
//
//        TFT_SCL(0);
//        dat <<= 1;
//    }
//    TFT_CS(1);
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ����������
////  @param      x_start     	����x��������
////  @param      y_start     	����y��������
////  @param      x_end       	����x������յ�
////  @param      y_end       	����y������յ�
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_set_region(0,0,10,10);// x��y����㶼��0���յ㶼��10
////-------------------------------------------------------------------------------------------------------------------
//void lcd_set_region(unsigned int x_start, unsigned int y_start, unsigned int x_end, unsigned int y_end)
//{
//
//#if (0 == TFT_DISPLAY_DIR || 1 == TFT_DISPLAY_DIR)
//    lcd_writeIndex(0x2a);
//    lcd_writeData(0x00);
//    lcd_writeData(x_start + 2);
//    lcd_writeData(0x00);
//    lcd_writeData(x_end + 2);
//
//    lcd_writeIndex(0x2b);
//    lcd_writeData(0x00);
//    lcd_writeData(y_start + 1);
//    lcd_writeData(0x00);
//    lcd_writeData(y_end + 1);
//
//#elif(2 == TFT_DISPLAY_DIR || 3 == TFT_DISPLAY_DIR)
//    lcd_writeIndex(0x2a);
//    lcd_writeData(0x00);
//    lcd_writeData(x_start+1);
//    lcd_writeData(0x0);
//    lcd_writeData(x_end+1);
//
//    lcd_writeIndex(0x2b);
//    lcd_writeData(0x00);
//    lcd_writeData(y_start+2);
//    lcd_writeData(0x00);
//    lcd_writeData(y_end+2);
//
//#endif
//
//    lcd_writeIndex(0x2c);
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ����������
////  @param      color     		��ɫ����
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_clear(YELLOW);// ȫ������Ϊ��ɫ
////-------------------------------------------------------------------------------------------------------------------
//void lcd_clear(int color)
//{
//    uint8_t i, j;
//    lcd_set_region(0, 0, TFT_X_MAX - 1, TFT_Y_MAX - 1);
//    for (i = 0; i < TFT_Y_MAX; i++)
//        for (j = 0; j < TFT_X_MAX; j++)
//            lcd_writedata_16bit(color);
//}
//
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ����ʼ��
////  @return     void
////  @since      v1.0
////  Sample usage:
////-------------------------------------------------------------------------------------------------------------------
//void lcd_init(void)
//{
//
//
//    BL(1);
//    REST(0);
////    systick_delay_ms(10);
//    REST(1);
////    systick_delay_ms(120);
//    lcd_writeIndex(0x11);
////    systick_delay_ms(120);
//
//    lcd_writeIndex(0xB1);
//    lcd_writeData(0x01);
//    lcd_writeData(0x2C);
//    lcd_writeData(0x2D);
//
//    lcd_writeIndex(0xB2);
//    lcd_writeData(0x01);
//    lcd_writeData(0x2C);
//    lcd_writeData(0x2D);
//
//    lcd_writeIndex(0xB3);
//    lcd_writeData(0x01);
//    lcd_writeData(0x2C);
//    lcd_writeData(0x2D);
//    lcd_writeData(0x01);
//    lcd_writeData(0x2C);
//    lcd_writeData(0x2D);
//
//    lcd_writeIndex(0xB4);
//    lcd_writeData(0x07);
//
//    lcd_writeIndex(0xC0);
//    lcd_writeData(0xA2);
//    lcd_writeData(0x02);
//    lcd_writeData(0x84);
//    lcd_writeIndex(0xC1);
//    lcd_writeData(0xC5);
//
//    lcd_writeIndex(0xC2);
//    lcd_writeData(0x0A);
//    lcd_writeData(0x00);
//
//    lcd_writeIndex(0xC3);
//    lcd_writeData(0x8A);
//    lcd_writeData(0x2A);
//    lcd_writeIndex(0xC4);
//    lcd_writeData(0x8A);
//    lcd_writeData(0xEE);
//
//    lcd_writeIndex(0xC5);
//    lcd_writeData(0x0E);
//
//    lcd_writeIndex(0x36);
//    switch (TFT_DISPLAY_DIR)//y x v
//    {
//        case 0:
//            lcd_writeData(1 << 7 | 1 << 6 | 0 << 5);
//            break;  //����ģʽ
//        case 1:
//            lcd_writeData(0 << 7 | 0 << 6 | 0 << 5);
//            break;  //����ģʽ  ��ת180
//        case 2:
//            lcd_writeData(1 << 7 | 0 << 6 | 1 << 5);
//            break;  //����ģʽ
//        case 3:
//            lcd_writeData(0 << 7 | 1 << 6 | 1 << 5);
//            break;  //����ģʽ  ��ת180
//    }
//
//    lcd_writeIndex(0xe0);
//    lcd_writeData(0x0f);
//    lcd_writeData(0x1a);
//    lcd_writeData(0x0f);
//    lcd_writeData(0x18);
//    lcd_writeData(0x2f);
//    lcd_writeData(0x28);
//    lcd_writeData(0x20);
//    lcd_writeData(0x22);
//    lcd_writeData(0x1f);
//    lcd_writeData(0x1b);
//    lcd_writeData(0x23);
//    lcd_writeData(0x37);
//    lcd_writeData(0x00);
//    lcd_writeData(0x07);
//    lcd_writeData(0x02);
//    lcd_writeData(0x10);
//
//    lcd_writeIndex(0xe1);
//    lcd_writeData(0x0f);
//    lcd_writeData(0x1b);
//    lcd_writeData(0x0f);
//    lcd_writeData(0x17);
//    lcd_writeData(0x33);
//    lcd_writeData(0x2c);
//    lcd_writeData(0x29);
//    lcd_writeData(0x2e);
//    lcd_writeData(0x30);
//    lcd_writeData(0x30);
//    lcd_writeData(0x39);
//    lcd_writeData(0x3f);
//    lcd_writeData(0x00);
//    lcd_writeData(0x07);
//    lcd_writeData(0x03);
//    lcd_writeData(0x10);
//
//    lcd_writeIndex(0x2a);
//    lcd_writeData(0x00);
//    lcd_writeData(0x00 + 2);
//    lcd_writeData(0x00);
//    lcd_writeData(0x80 + 2);
//
//    lcd_writeIndex(0x2b);
//    lcd_writeData(0x00);
//    lcd_writeData(0x00 + 3);
//    lcd_writeData(0x00);
//    lcd_writeData(0x80 + 3);
//
//    lcd_writeIndex(0xF0);
//    lcd_writeData(0x01);
//    lcd_writeIndex(0xF6);
//    lcd_writeData(0x00);
//
//    lcd_writeIndex(0x3A);
//    lcd_writeData(0x05);
//    lcd_writeIndex(0x29);
//
//    lcd_clear(BLACK);//ȫ��
//}
//
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ������
////  @param      x     	        ����x��������
////  @param      y     	        ����y��������
////  @param      dat       	    ��Ҫ��ʾ����ɫ
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_drawpoint(0,0,RED);  //����0,0��һ����ɫ�ĵ�
////-------------------------------------------------------------------------------------------------------------------
//void lcd_drawpoint(uint16 x, uint16 y, uint16 color)
//{
//    lcd_set_region(x, y, x, y);
//    lcd_writedata_16bit(color);
//}
//
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ����ʾ�ַ�
////  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
////  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX-1��
////  @param      dat       	    ��Ҫ��ʾ���ַ�
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showchar(0,0,'x');//����0,0дһ���ַ�x
////-------------------------------------------------------------------------------------------------------------------
//void lcd_showchar(uint16 x, uint16 y, uint8_t dat)
//{
//    uint8_t i, j;
//    uint8_t temp;
//
//    for (i = 0; i < 16; i++)
//    {
//        lcd_set_region(x, y + i, x + 7, y + i);
//        temp = tft_ascii_1[dat - 32][i];//��32��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո���ascii�������32
//        for (j = 0; j < 8; j++)
//        {
//            if (temp & 0x01) lcd_writedata_16bit(PEN_COLOR);
//            else lcd_writedata_16bit(BACKGROUND_COLOR);
//            temp >>= 1;
//        }
//    }
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ����ʾ�ַ���
////  @param      x     	        ����x��������  ������Χ 0 -��TFT_X_MAX-1��
////  @param      y     	        ����y��������  ������Χ 0 -��TFT_Y_MAX/16-1��
////  @param      dat       	    ��Ҫ��ʾ���ַ���
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showstr(0,0,"seekfree");
////-------------------------------------------------------------------------------------------------------------------
//void lcd_showstr(uint16 x, uint16 y, uint8_t dat[])
//{
//    uint16 j;
//
//    j = 0;
//    while (dat[j] != '\0')
//    {
//        lcd_showchar(x + 8 * j, y * 16, dat[j]);
//        j++;
//    }
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ����ʾ8λ�з���
////  @param      x     	        ����x��������  ������Χ 0 -��TFT_X_MAX-1��
////  @param      y     	        ����y��������  ������Χ 0 -��TFT_Y_MAX/16-1��
////  @param      dat       	    ��Ҫ��ʾ�ı�������������int8
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showint8(0,0,x);//xΪint8����
////-------------------------------------------------------------------------------------------------------------------
//void lcd_showint8(uint16 x, uint16 y, int8_t dat)
//{
//    uint8_t a[3];
//    uint8_t i;
//    if (dat < 0)
//    {
//        lcd_showchar(x, y * 16, '-');
//        dat = -dat;
//    } else lcd_showchar(x, y * 16, ' ');
//
//    a[0] = dat / 100;
//    a[1] = dat / 10 % 10;
//    a[2] = dat % 10;
//    i = 0;
//    while (i < 3)
//    {
//        lcd_showchar(x + (8 * (i + 1)), y * 16, '0' + a[i]);
//        i++;
//    }
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ����ʾ8λ�޷���
////  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
////  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
////  @param      dat       	    ��Ҫ��ʾ�ı�������������uint8
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showuint8(0,0,x);//xΪuint8����
////-------------------------------------------------------------------------------------------------------------------
//void lcd_showuint8(uint16 x, uint16 y, uint8_t dat)
//{
//    uint8_t a[3];
//    uint8_t i;
//
//    a[0] = dat / 100;
//    a[1] = dat / 10 % 10;
//    a[2] = dat % 10;
//    i = 0;
//    while (i < 3)
//    {
//        lcd_showchar(x + (8 * i), y * 16, '0' + a[i]);
//        i++;
//    }
//
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ����ʾ16λ�з���
////  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
////  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
////  @param      dat       	    ��Ҫ��ʾ�ı�������������int16
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showint16(0,0,x);//xΪint16����
////-------------------------------------------------------------------------------------------------------------------
//void lcd_showint16(uint16 x, uint16 y, int16_t dat)
//{
//    uint8_t a[5];
//    uint8_t i;
//    if (dat < 0)
//    {
//        lcd_showchar(x, y * 16, '-');
//        dat = -dat;
//    } else lcd_showchar(x, y * 16, ' ');
//
//    a[0] = dat / 10000;
//    a[1] = dat / 1000 % 10;
//    a[2] = dat / 100 % 10;
//    a[3] = dat / 10 % 10;
//    a[4] = dat % 10;
//
//    i = 0;
//    while (i < 5)
//    {
//        lcd_showchar(x + (8 * (i + 1)), y * 16, '0' + a[i]);
//        i++;
//    }
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      Һ����ʾ16λ�޷���
////  @param      x     	        ����x�������� ������Χ 0 -��TFT_X_MAX-1��
////  @param      y     	        ����y�������� ������Χ 0 -��TFT_Y_MAX/16-1��
////  @param      dat       	    ��Ҫ��ʾ�ı�������������uint16
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showuint16(0,0,x);//xΪuint16����
////-------------------------------------------------------------------------------------------------------------------
//void lcd_showuint16(uint16 x, uint16 y, uint16 dat)
//{
//    uint8_t a[5];
//    uint8_t i;
//
//    a[0] = dat / 10000;
//    a[1] = dat / 1000 % 10;
//    a[2] = dat / 100 % 10;
//    a[3] = dat / 10 % 10;
//    a[4] = dat % 10;
//
//    i = 0;
//    while (i < 5)
//    {
//        lcd_showchar(x + (8 * i), y * 16, '0' + a[i]);
//        i++;
//    }
//}
