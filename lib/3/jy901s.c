/*
 * @Author: Ptisak
 * @Date: 2022-07-27 20:25:34
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-31 01:07:03
 * @Version: Do not edit
 */
#include "jy901s.h"

struct SAcc stcAcc;
struct SGyro stcGyro;
struct SAngle stcAngle;

float damping = 0;
float diansai_z_kp = 0.01;

void jy901s_handler(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;
	ucRxBuffer[ucRxCnt++] = ucData; //���յ������ݴ��뻺������
	if (ucRxBuffer[0] != 0x55)		//����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt = 0;
		return;
	}
	if (ucRxCnt < 11)
	{
		return;
	} //���ݲ���11�����򷵻�
	else
	{
		switch (ucRxBuffer[1]) //�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		{
		// memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
		case 0x51:
			memcpy(&stcAcc, &ucRxBuffer[2], 8);
			break;
		case 0x52:
			memcpy(&stcGyro, &ucRxBuffer[2], 8);
			// diansai_z_kp = map(basic_speed, -200, 200, -1, 1);
			damping = diansai_z_kp * stcGyro.w[2];
			break;
		//����ҪZ��Ƕ�����
		case 0x53:
			memcpy(&stcAngle, &ucRxBuffer[2], 8);
			break;
		}
		ucRxCnt = 0; //��ջ�����
	}
}

void get_damping(void)
{

	//�������ǵ�z�ܽǼ��ٶȵ���������΢�ֻ���������
	// printf("%d \r\n",(int)(stcAngle.Angle[2] / 32768 * 180));
	//	printf("%d \r\n",stcGyro.w[2]);
	//	printf("%d \r\n",stcAcc.a[2]);
	//	damping = diansai_z_kp * (*(float*)(&(stcGyro.w[2]))) / 32768 * 2000;
	// damping = (float)stcGyro.w[2]/32768*2000;
}
