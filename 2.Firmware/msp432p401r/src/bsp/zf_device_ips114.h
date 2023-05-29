/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          zf_device_ips114
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚             单片机管脚
*                   SCL                  查看 zf_device_ips114.h 中 IPS114_SCL_PIN 宏定义
*                   SDA                  查看 zf_device_ips114.h 中 IPS114_SDA_PIN 宏定义
*                   RST                  查看 zf_device_ips114.h 中 IPS114_RST_PIN 宏定义
*                   DC                   查看 zf_device_ips114.h 中 IPS114_DC_PIN 宏定义
*                   CS                   查看 zf_device_ips114.h 中 IPS114_CS_PIN 宏定义
*                   BLK                  查看 zf_device_ips114.h 中 IPS114_BLK_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   最大分辨率 135 * 240
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_ips114_h_
#define _zf_device_ips114_h_

#include <driverlib.h>
#include "driver/user_spi.h"
#include "common_font.h"

#define IPS114_SPI_SPEED                (24 * 1000 * 1000)                      // 硬件 SPI 速率 这里设置为系统时钟二分频
#define IPS114_SPI                      (EUSCI_B0_BASE)
#define IPS114_SCL_PIN                  (SPI_B0_CLK_P15)                           // 硬件 SPI SCK 引脚
#define IPS114_SDA_PIN                  (SPI_B0_MOSI_P16)                          // 硬件 SPI MOSI 引脚

#define IPS114_RST_PORT                  (GPIO_PORT_P5 )                                   // 液晶复位引脚定义
#define IPS114_RST_PIN                  (GPIO_PIN2 )                                   // 液晶复位引脚定义
#define IPS114_DC_PORT                   (GPIO_PORT_P5 )                                   // 液晶命令位引脚定义
#define IPS114_DC_PIN                   (GPIO_PIN0 )                                   // 液晶命令位引脚定义
#define IPS114_CS_PORT                   (GPIO_PORT_P1 )                                   // CS 片选引脚
#define IPS114_CS_PIN                   (GPIO_PIN7 )                                   // CS 片选引脚
#define IPS114_BLK_PORT                  (GPIO_PORT_P3 )                                   // 液晶背光引脚定义
#define IPS114_BLK_PIN                  (GPIO_PIN6 )                                   // 液晶背光引脚定义

#define IPS114_DEFAULT_DISPLAY_DIR      (IPS114_CROSSWISE)                  // 默认的显示方向
#define IPS114_DEFAULT_PENCOLOR         (RGB565_RED)                            // 默认的画笔颜色
#define IPS114_DEFAULT_BGCOLOR          (RGB565_WHITE)                          // 默认的背景颜色
#define IPS114_DEFAULT_DISPLAY_FONT     (IPS114_8X16_FONT)                      // 默认的字体模式

#define IPS114_DC(x)                    ((x) ? (GPIO_setOutputHighOnPin(IPS114_DC_PORT, IPS114_DC_PIN)) : (GPIO_setOutputLowOnPin(IPS114_DC_PORT, IPS114_DC_PIN)))
#define IPS114_RST(x)                   ((x) ? (GPIO_setOutputHighOnPin(IPS114_RST_PORT, IPS114_RST_PIN)) : (GPIO_setOutputLowOnPin(IPS114_RST_PORT, IPS114_RST_PIN)))
#define IPS114_CS(x)                    ((x) ? (GPIO_setOutputHighOnPin(IPS114_CS_PORT, IPS114_CS_PIN)) : (GPIO_setOutputLowOnPin(IPS114_CS_PORT, IPS114_CS_PIN)))
#define IPS114_BLK(x)                   ((x) ? (GPIO_setOutputHighOnPin(IPS114_BLK_PORT, IPS114_BLK_PIN)) : (GPIO_setOutputLowOnPin(IPS114_BLK_PORT, IPS114_BLK_PIN)))

typedef enum
{
    IPS114_PORTAIT                      = 0,                                    // 竖屏模式
    IPS114_PORTAIT_180                  = 1,                                    // 竖屏模式  旋转180
    IPS114_CROSSWISE                    = 2,                                    // 横屏模式
    IPS114_CROSSWISE_180                = 3,                                    // 横屏模式  旋转180
}ips114_dir_enum;

typedef enum
{
    IPS114_6X8_FONT                     = 0,                                    // 6x8      字体
    IPS114_8X16_FONT                    = 1,                                    // 8x16     字体
    IPS114_16X16_FONT                   = 2,                                    // 16x16    字体 目前不支持
}ips114_font_size_enum;

void    ips114_clear                    (void);
void    ips114_full                     (const uint16_t color);
void    ips114_set_dir                  (ips114_dir_enum dir);
void    ips114_set_font                 (ips114_font_size_enum font);
void    ips114_set_color                (const uint16_t pen, const  uint16_t bgcolor);
void    ips114_draw_point               (uint16_t x, uint16_t y, const uint16_t color);
void    ips114_draw_line                (uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, const uint16_t color);

void    ips114_show_char                (uint16_t x, uint16_t y, const char dat);
void    ips114_show_string              (uint16_t x, uint16_t y, const char dat[]);
void    ips114_show_int                 (uint16_t x,uint16_t y, const int32_t dat, uint8_t num);
void    ips114_show_uint                (uint16_t x,uint16_t y, const uint32_t dat, uint8_t num);
void    ips114_show_float               (uint16_t x,uint16_t y, const float dat, uint8_t num, uint8_t pointnum);

void    ips114_show_binary_image        (uint16_t x, uint16_t y, const uint8_t *image, uint16_t width, uint16_t height, uint16_t dis_width, uint16_t dis_height);
void    ips114_show_gray_image          (uint16_t x, uint16_t y, const uint8_t *image, uint16_t width, uint16_t height, uint16_t dis_width, uint16_t dis_height, uint8_t threshold);
void    ips114_show_rgb565_image        (uint16_t x, uint16_t y, const uint16_t *image, uint16_t width, uint16_t height, uint16_t dis_width, uint16_t dis_height, uint8_t color_mode);

void    ips114_show_wave                (uint16_t x, uint16_t y, const uint16_t *wave, uint16_t width, uint16_t value_max, uint16_t dis_width, uint16_t dis_value_max);
void    ips114_show_chinese             (uint16_t x, uint16_t y, uint8_t size, const uint8_t *chinese_buffer, uint8_t number, const uint16_t color);


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 显示小钻风图像
// 参数说明     p               图像数组
// 参数说明     width           显示宽度
// 参数说明     height          显示高度
// 返回参数     void
// 使用示例     ips114_displayimage7725(ov7725_image_binary[0], 80, 60);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define ips114_displayimage7725(p, width, height)       (ips114_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 显示总钻风图像 不带二值化 显示灰度图像
// 参数说明     p               图像数组
// 参数说明     width           显示宽度
// 参数说明     height          显示高度
// 返回参数     void
// 使用示例     ips114_displayimage03x(mt9v03x_image[0], 94, 60);
// 备注信息     如果要显示二值化图像就去调用 ips114_show_gray_image 函数
//-------------------------------------------------------------------------------------------------------------------
#define ips114_displayimage03x(p, width, height)        (ips114_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS114 显示凌瞳图像
// 参数说明     p               图像数组
// 参数说明     width           显示宽度
// 参数说明     height          显示高度
// 返回参数     void
// 使用示例     ips114_displayimage8660(scc8660_image[0], 80, 60);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define ips114_displayimage8660(p, width, height)       (ips114_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))

void    ips114_init                     (void);

#endif
