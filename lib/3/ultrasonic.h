/*
 * @Author: Ptisak
 * @Date: 2022-07-27 21:42:41
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-29 23:42:48
 * @Version: Do not edit
 */
#ifndef MY_ULTRASONIC_H
#define MY_ULTRASONIC_H

#include "psk_ALL.h"
extern float ultrasonic_distance;

#define SPLIT_ULTRASONIC_UART EUSCI_A2_BASE //�������մ���
#define SPLIT_ULTRASONIC_BAUD 115200
#define SPLIT_ULTRASONIC_RX GPIO_PORT_P3, GPIO_PIN3 //��Ӧ����tx
#define SPLIT_ULTRASONIC_TX GPIO_PORT_P3, GPIO_PIN2 //��Ӧ����rx

#define SEND_PORT_PIN GPIO_PORT_P6, GPIO_PIN0 //��ȥEN�ˣ����߼���

void uart_handle(void);
void send_init(void);

#endif