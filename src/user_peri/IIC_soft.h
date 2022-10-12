#ifndef _IIC_H
#define _IIC_H

#include "driverlib.h" 
#include "header.h" 

#define SEEKFREE_SCL 3, 7 //定义SCL引脚  可任意更改为其他IO
#define SEEKFREE_SDA 3, 6 //定义SDA引脚  可任意更改为其他IO

#define SIMIIC_DELAY_TIME 2

typedef enum IIC // IIC类型枚举
{
	SIMIIC,
	SCCB
} IIC_type;

extern uint16_t simiic_delay_time; // ICM等传感器应设置为20

void simiic_delay_set(uint16_t time);
void simiic_start(void);
void simiic_stop(void);
void simiic_ack_main(uint8_t ack_main);
void send_ch(uint8_t c);
uint8_t read_ch(uint8_t ack);
void simiic_write_reg(uint8_t dev_add, uint8_t reg, uint8_t dat);
void simiic_write_regs(uint8_t dev_add, uint8_t reg, uint8_t *dat_add, uint8_t num);

uint8_t simiic_read_reg(uint8_t dev_add, uint8_t reg, IIC_type type);
void simiic_read_regs(uint8_t dev_add, uint8_t reg, uint8_t *dat_add, uint8_t num, IIC_type type);
void simiic_init(void);


#endif

