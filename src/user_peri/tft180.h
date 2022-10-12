/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,????
 * All rights reserved.
 * ????QQ?:??:179029047(??)  ??:244861897  ??:824575535
 *
 * ????????????????,????????????,
 * ????????????,???????????????????
 *
 * @file       		TFT
 * @company	   		??????????
 * @author     		????(QQ3184284598)
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-11-20
 * @note		
 ********************************************************************************************************************/



#ifndef _SEEKFREE_18TFT_h
#define _SEEKFREE_18TFT_h

#include <gpio.h>
#include "font.h"

typedef unsigned char  uint8;
typedef  short         int16;

#define TFT_SCL_port   GPIO_PORT_P1
#define TFT_SCL_pin    GPIO_PIN5 

#define TFT_SDA_PORT   GPIO_PORT_P1
#define TFT_SDA_Pin    GPIO_PIN6

#define REST_PORT      GPIO_PORT_P5
#define REST_Pin       GPIO_PIN0

#define DC_PORT        GPIO_PORT_P1
#define DC_Pin         GPIO_PIN7

#define TFT_CS_PORT    GPIO_PORT_P4
#define TFT_CS_Pin     GPIO_PIN6

#define BL_PORT        GPIO_PORT_P6
#define BL_Pin         GPIO_PIN5


//--------------???IO??--------------
           	

// Color
#define RED     	0XF800
#define GREEN   	0X07E0
#define BLUE    	0X001F
#define PURPLE    	0XF81F
#define CYAN   	    0X07FF
#define BLACK   	0X0000
#define WHITE   	0XFFFF
#define YELLOW  	0xFFE0


#define PENCOLOR    WHITE
#define BGCOLOR	    BLACK

     
     
//??????
//0 ????
//1 ????  ??180
//2 ????
//3 ????  ??180
#define TFT_DISPLAY_DIR 0

//#if (0==TFT_DISPLAY_DIR || 1==TFT_DISPLAY_DIR)
#define	TFT_X_MAX	128	//??X???
#define TFT_Y_MAX	160 //??Y???
//     
//#elif (2==TFT_DISPLAY_DIR || 3==TFT_DISPLAY_DIR)
//#define	TFT_X_MAX	160	//??X???
//#define TFT_Y_MAX	128 //??Y???
//     
//#else
//#error "TFT_DISPLAY_DIR ????"



void lcd_init(void);
void lcd_clear(int color);
void lcd_drawpoint(uint16 x,uint16 y,uint16 color);
void lcd_showchar(uint16 x,uint16 y,uint8 dat);
void lcd_showstr(uint16 x,uint16 y,uint8 dat[]);
void lcd_showint8(uint16 x,uint16 y,int8_t dat);
void lcd_showuint8(uint16 x,uint16 y,uint8 dat);
void lcd_showint16(uint16 x,uint16 y,int16 dat);
void lcd_showuint16(uint16 x,uint16 y,uint16 dat);

#endif
