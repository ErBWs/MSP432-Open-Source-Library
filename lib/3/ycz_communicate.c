/*
 * @Author: Ptisak
 * @Date: 2022-07-27 20:26:37
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-31 10:26:13
 * @Version: Do not edit
 */
#include "ycz_communicate.h"
float others_speed;
//ÿ�����ϱ��Լ���ʵʱ�ٶ�
//��ڲ�����ÿ�����ڵ��ٶȣ���λcm/���ڣ����ÿ����΢�����һ��
void speed_post(uint8 speed_cm)
{
	uint8 send_buffer[4];

	send_buffer[0] = 0x55;
	send_buffer[1] = 0xbb; // 0xbb��ʾ�����ٶ�

	if (speed_cm = 0x55) //�ܿ�֡ͷ
		send_buffer[2] = 0x56;
	else
		send_buffer[2] = speed_cm;

	send_buffer[3] = 0xdd;

	MAP_UART_transmitData(EUSCI_A1_BASE, send_buffer[0]);
	MAP_UART_transmitData(EUSCI_A1_BASE, send_buffer[1]);
	MAP_UART_transmitData(EUSCI_A1_BASE, send_buffer[2]);
	MAP_UART_transmitData(EUSCI_A1_BASE, send_buffer[3]);
}

void task_post(uint8 pos)
{
	MAP_UART_transmitData(EUSCI_A1_BASE, 0x55);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xaa);
	MAP_UART_transmitData(EUSCI_A1_BASE, pos);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xdd);
}

void task_and_speed_post(uint8 task_number, uint8 speed)
{
	MAP_UART_transmitData(EUSCI_A1_BASE, 0x55);
	MAP_UART_transmitData(EUSCI_A1_BASE, task_number);
	MAP_UART_transmitData(EUSCI_A1_BASE, speed);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xdd);
}
void task_and_speed_post_A0(uint8 task_number, uint8 speed)
{
	MAP_UART_transmitData(EUSCI_A0_BASE, 0x55);
	MAP_UART_transmitData(EUSCI_A0_BASE, task_number);
	MAP_UART_transmitData(EUSCI_A0_BASE, speed);
	MAP_UART_transmitData(EUSCI_A0_BASE, 0xdd);
}
extern int buzzer_bi_flag;
extern float basic_speed;
void communicate_handler(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;
	ucRxBuffer[ucRxCnt++] = ucData; //���յ������ݴ��뻺������

	if (ucRxBuffer[0] != 0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt = 0;
		return;
	}
	if (ucRxCnt < 4)
	{
		return;
	} //���ݲ���4�����򷵻�
	else
	{
		if (ucRxBuffer[3] != 0xdd) //֡βУ��
		{
			ucRxCnt = 0;
			return;
		}

		if (ucRxBuffer[1] == 0xaa) //�����ֽ�
		{
			// task_state = ucRxBuffer[2];
		}

		if (ucRxBuffer[2] == 0xbb) //�ٶ��ֽ�
		{
			others_speed = ucRxBuffer[2];
		}
		if (ucRxBuffer[3] == 0xcc) //�ٶ��ֽ�
		{
			basic_speed = (float)ucRxBuffer[2];
		}

		ucRxCnt = 0; //��ջ�����
	}
}

void task_stop(void)
{
	MAP_UART_transmitData(EUSCI_A1_BASE, 0x55);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xcc);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xcc);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xdd);
}
void task_stop_A0(void)
{
	MAP_UART_transmitData(EUSCI_A0_BASE, 0x55);
	MAP_UART_transmitData(EUSCI_A0_BASE, 0xcc);
	MAP_UART_transmitData(EUSCI_A0_BASE, 0xcc);
	MAP_UART_transmitData(EUSCI_A0_BASE, 0xdd);
}