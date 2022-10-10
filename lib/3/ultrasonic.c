/*
 * @Author: Ptisak
 * @Date: 2022-07-29 23:25:22
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-29 23:42:02
 * @Version: Do not edit
 */
#include "ultrasonic.h"

uint16 ranging_counter = 0; // �������
uint8 ranging_flage = 0x00; // ���״̬

uint8 receipt_data;
uint8 dat[3];
uint8 num;

float ultrasonic_distance; // cm
void uart_handler(void)
{
    receipt_data = MAP_UART_receiveData(SPLIT_ULTRASONIC_UART);
    dat[num] = receipt_data;
    if (dat[0] != 0xa5)
        num = 0; //����һ�������Ƿ�Ϊ0xa5
    else
        num++;

    if (num == 3) //������� ��ʼ��������
    {
        num = 0;
        ranging_counter = dat[1] << 8 | dat[2]; //�õ�������ģ�����ľ���
        ultrasonic_distance = ranging_counter / 10;
    }
}

void send_init(void)
{
    GPIO_SET(6, 0, 1);
}
