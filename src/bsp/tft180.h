///*********************************************************************************************************************
// * COPYRIGHT NOTICE
// * Copyright (c) 2018,????
// * All rights reserved.
// * ????QQ?:??:179029047(??)  ??:244861897  ??:824575535
// *
// * ????????????????,????????????,
// * ????????????,???????????????????
// *
// * @file       		TFT
// * @company	   		??????????
// * @author     		????(QQ3184284598)
// * @Taobao   		https://seekfree.taobao.com/
// * @date       		2019-11-20
// * @note
// ********************************************************************************************************************/
//
//
//
//#ifndef _tft180_h_
//#define _tft180_h_
//
//#include <driverlib.h>
//#include "header.h"
//#include "font.h"
//
//#define USE_SOFT_SPI            (0)
//#if USE_SOFT_SPI
////--------------------------------------------------------------------------
//#define TFT180_SCL_PORT         GPIO_PORT_P1
//#define TFT180_SCL_PIN          GPIO_PIN5
//
//#define TFT180_SDA_PORT         GPIO_PORT_P1
//#define TFT180_SDA_PIN          GPIO_PIN6
////--------------------------------------------------------------------------
//#else
////--------------------------------------------------------------------------
//#define TFT180_SPI_SPEED        16000000
//#define TFT180_SCL_PIN          SPI_B0_CLK_P15
//#define TFT180_SDA_Pin          SPI_B0_MOSI_P16
////--------------------------------------------------------------------------
//
//#define TFT180_RST_PORT         GPIO_PORT_P5
//#define TFT180_RST_PIN          GPIO_PIN0
//
//#define TFT180_DC_PORT          GPIO_PORT_P1
//#define TFT180_DC_PIN           GPIO_PIN7
//
//#define TFT180_CS_PORT          GPIO_PORT_P4
//#define TFT180_CS_PIN           GPIO_PIN6
//
//#define TFT180_BL_PORT          GPIO_PORT_P6
//#define TFT180_BL_PIN           GPIO_PIN5
//
//#define TFT180_RST(x)           ((x) ? (GPIO_setOutputHighOnPin(TFT180_RST_PORT, TFT180_RST_PIN)) :     \
//                                        (GPIO_setOutputLowOnPin(TFT180_RST_PORT, TFT180_RST_PIN)))
//#define TFT180_DC(x)            ((x) ? (GPIO_setOutputHighOnPin(TFT180_DC_PORT, TFT180_DC_PIN)) :     \
//                                        (GPIO_setOutputLowOnPin(TFT180_DC_PORT, TFT180_DC_PIN)))
//
//
//// Color
//#define RED     	0XF800
//#define GREEN   	0X07E0
//#define BLUE    	0X001F
//#define PURPLE    	0XF81F
//#define CYAN   	    0X07FF
//#define BLACK   	0X0000
//#define WHITE   	0XFFFF
//#define YELLOW  	0xFFE0
//
//#define PEN_COLOR               WHITE
//#define BACKGROUND_COLOR	    BLACK
//
//
//
////??????
////0 ????
////1 ????  ??180
////2 ????
////3 ????  ??180
//#define TFT_DISPLAY_DIR 0
//
////#if (0==TFT_DISPLAY_DIR || 1==TFT_DISPLAY_DIR)
//#define	TFT_X_MAX	128	//??X???
//#define TFT_Y_MAX	160 //??Y???
////
////#elif (2==TFT_DISPLAY_DIR || 3==TFT_DISPLAY_DIR)
////#define	TFT_X_MAX	160	//??X???
////#define TFT_Y_MAX	128 //??Y???
////
////#else
////#error "TFT_DISPLAY_DIR ????"
//
//
//
//void lcd_init(void);
//void lcd_clear(int color);
//void lcd_drawpoint(uint16 x,uint16 y,uint16 color);
//void lcd_showchar(uint16 x, uint16 y, uint8_t dat);
//void lcd_showstr(uint16 x, uint16 y, uint8_t dat[]);
//void lcd_showint8(uint16 x,uint16 y,int8_t dat);
//void lcd_showuint8(uint16 x, uint16 y, uint8_t dat);
//void lcd_showint16(uint16 x, uint16 y, int16_t dat);
//void lcd_showuint16(uint16 x,uint16 y,uint16 dat);
//
//#endif