///*********************************************************************************************************************
// * COPYRIGHT NOTICE
// * Copyright (c) 2018,逐飞科技
// * All rights reserved.
// * 技术讨论QQ群：一群：179029047(已满)  二群：244861897  三群：824575535
// *
// * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
// * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
// *
// * @file       		TFT
// * @company	   		成都逐飞科技有限公司
// * @author     		逐飞科技(QQ3184284598)
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
//void lcd_writeIndex(uint8_t dat)            //写命令
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
//void lcd_writeData(uint8_t dat)            //写数据
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
//void lcd_writedata_16bit(uint16 dat)    //向液晶屏写一个16位数据
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
////  @brief      液晶坐标设置
////  @param      x_start     	坐标x方向的起点
////  @param      y_start     	坐标y方向的起点
////  @param      x_end       	坐标x方向的终点
////  @param      y_end       	坐标y方向的终点
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_set_region(0,0,10,10);// x、y的起点都是0，终点都是10
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
////  @brief      液晶清屏函数
////  @param      color     		颜色设置
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_clear(YELLOW);// 全屏设置为黄色
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
////  @brief      液晶初始化
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
//            break;  //竖屏模式
//        case 1:
//            lcd_writeData(0 << 7 | 0 << 6 | 0 << 5);
//            break;  //竖屏模式  旋转180
//        case 2:
//            lcd_writeData(1 << 7 | 0 << 6 | 1 << 5);
//            break;  //横屏模式
//        case 3:
//            lcd_writeData(0 << 7 | 1 << 6 | 1 << 5);
//            break;  //横屏模式  旋转180
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
//    lcd_clear(BLACK);//全白
//}
//
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      液晶画点
////  @param      x     	        坐标x方向的起点
////  @param      y     	        坐标y方向的起点
////  @param      dat       	    需要显示的颜色
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_drawpoint(0,0,RED);  //坐标0,0画一个红色的点
////-------------------------------------------------------------------------------------------------------------------
//void lcd_drawpoint(uint16 x, uint16 y, uint16 color)
//{
//    lcd_set_region(x, y, x, y);
//    lcd_writedata_16bit(color);
//}
//
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      液晶显示字符
////  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
////  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX-1）
////  @param      dat       	    需要显示的字符
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showchar(0,0,'x');//坐标0,0写一个字符x
////-------------------------------------------------------------------------------------------------------------------
//void lcd_showchar(uint16 x, uint16 y, uint8_t dat)
//{
//    uint8_t i, j;
//    uint8_t temp;
//
//    for (i = 0; i < 16; i++)
//    {
//        lcd_set_region(x, y + i, x + 7, y + i);
//        temp = tft_ascii_1[dat - 32][i];//减32因为是取模是从空格开始取得 空格在ascii中序号是32
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
////  @brief      液晶显示字符串
////  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
////  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
////  @param      dat       	    需要显示的字符串
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
////  @brief      液晶显示8位有符号
////  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
////  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
////  @param      dat       	    需要显示的变量，数据类型int8
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showint8(0,0,x);//x为int8类型
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
////  @brief      液晶显示8位无符号
////  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
////  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
////  @param      dat       	    需要显示的变量，数据类型uint8
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showuint8(0,0,x);//x为uint8类型
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
////  @brief      液晶显示16位有符号
////  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
////  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
////  @param      dat       	    需要显示的变量，数据类型int16
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showint16(0,0,x);//x为int16类型
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
////  @brief      液晶显示16位无符号
////  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
////  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
////  @param      dat       	    需要显示的变量，数据类型uint16
////  @return     void
////  @since      v1.0
////  Sample usage:               lcd_showuint16(0,0,x);//x为uint16类型
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
