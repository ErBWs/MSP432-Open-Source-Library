/*
 * @Author: Ptisak
 * @Date: 2022-07-21 13:39:12
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-24 22:57:04
 * @Version: Do not edit
 */
/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		ģ��IIC
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 * @note
					���߶��壺
					------------------------------------
						SCL                 �鿴SEEKFREE_IIC�ļ��ڵ�SEEKFREE_SCL�궨��
						SDA                 �鿴SEEKFREE_IIC�ļ��ڵ�SEEKFREE_SDA�궨��
					------------------------------------
 ********************************************************************************************************************/

#ifndef _SEEKFREE_IIC_h
#define _SEEKFREE_IIC_h

#include <psk_ALL.h>

#define SEEKFREE_SCL 3, 7 //����SCL����  ���������Ϊ����IO
#define SEEKFREE_SDA 3, 6 //����SDA����  ���������Ϊ����IO

#define SIMIIC_DELAY_TIME 2

typedef enum IIC // IIC����ö��
{
	SIMIIC,
	SCCB
} IIC_type;

extern uint16 simiic_delay_time; // ICM�ȴ�����Ӧ����Ϊ20

void simiic_delay_set(uint16 time);
void simiic_start(void);
void simiic_stop(void);
void simiic_ack_main(uint8 ack_main);
void send_ch(uint8 c);
uint8 read_ch(uint8 ack);
void simiic_write_reg(uint8 dev_add, uint8 reg, uint8 dat);
void simiic_write_regs(uint8 dev_add, uint8 reg, uint8 *dat_add, uint8 num);

uint8 simiic_read_reg(uint8 dev_add, uint8 reg, IIC_type type);
void simiic_read_regs(uint8 dev_add, uint8 reg, uint8 *dat_add, uint8 num, IIC_type type);
void simiic_init(void);

#endif
