/*
 * @Author: Ptisak
 * @Date: 2022-07-29 08:51:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-29 08:59:31
 * @Version: Do not edit
 */
#ifndef __COND_H
#define __COND_H
#include "psk_ALL.h"

#define NO_condition 0 //
                       //
// #define LEFT45 1          //����??45���а���ʱ
// #define LEFT90 2          //
// #define LEFT135 3         //
//                           //
// #define RIGHT45 4         //
// #define RIGHT90 5         //����??90���а���ʱ
// #define RIGHT135 6        //
//                           //
// #define UPHILL 7          //
// #define DOWNHILL 8        //��???�����µ�״̬ʱ    angle_y > 21.5f
// #define FLAT 9            //��???��ƽ̹��״̬ʱ    angle_y > -5.0f && angle_y < 5.0f
//                           //
// #define LINEINMIDDLE 10   //�����м�???�⵽����??  Laser_detect[3] || Laser_detect[4]
//                           //
// #define NOT_UPHILL 11     //
// #define NOT_DOWNHILL 12   //�����������µ�״̬ʱ  angle_y < 21.5f
// #define NOT_FLAT 13       //��������ƽ̹��״̬ʱ  angle_y < -5.0f || angle_y > 5.0f
//                           //
// #define SEESAW 14         //�����ΰ�??           angle_x - angle_y > 5.0f
// #define ANGLE_Y_CHANGE 15 //�Ƕ�Y�仯??, ��???�仯��Χ??2��

// #define OBSTACLE 16 //������???ʱ??������ʱ

#define LEFT_HAVE_LINE 17
#define RIGHT_HAVE_LINE 18

// #define COLLISION 19 //��ײ����???�⵽��ײ

#define STOP_LINE 20

extern int now_condition;
extern u8 condition_str[][7];

void wait_for_condition(int c); //�ȴ����������˳���??

int is_condition(int c); //����??��???��ָ������

#endif
