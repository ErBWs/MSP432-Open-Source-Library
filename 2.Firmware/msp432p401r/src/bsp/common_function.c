/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 */

#include "common_function.h"


void func_int_to_str (char *str, int32_t number)
{
    uint8_t data_temp[16];                                                        // ������
    uint8_t bit = 0;                                                              // ����λ��
    int32_t number_temp = 0;

    do
    {
        if(NULL == str)
        {
            break;
        }

        if(0 > number)                                                          // ����
        {
            *str ++ = '-';
            number = -number;
        }
        else if(0 == number)                                                    // �������Ǹ� 0
        {
            *str = '0';
            break;
        }

        while(0 != number)                                                      // ѭ��ֱ����ֵ����
        {
            number_temp = number % 10;
            data_temp[bit ++] = abs(number_temp);                          // ������ֵ��ȡ����
            number /= 10;                                                       // ��������ȡ�ĸ�λ��
        }
        while(0 != bit)                                                         // ��ȡ�����ָ����ݼ�����
        {
            *str ++ = (data_temp[bit - 1] + 0x30);                              // �����ִӵ��������е���ȡ�� �����������ַ���
            bit --;
        }
    }while(0);
}


void func_uint_to_str (char *str, uint32_t number)
{
    int8_t data_temp[16];                                                         // ������
    uint8_t bit = 0;                                                              // ����λ��

    do
    {
        if(NULL == str)
        {
            break;
        }

        if(0 == number)                                                         // ���Ǹ� 0
        {
            *str = '0';
            break;
        }

        while(0 != number)                                                      // ѭ��ֱ����ֵ����
        {
            data_temp[bit ++] = (number % 10);                                  // ������ֵ��ȡ����
            number /= 10;                                                       // ��������ȡ�ĸ�λ��
        }
        while(0 != bit)                                                         // ��ȡ�����ָ����ݼ�����
        {
            *str ++ = (data_temp[bit - 1] + 0x30);                              // �����ִӵ��������е���ȡ�� �����������ַ���
            bit --;
        }
    }while(0);
}


void func_float_to_str (char *str, float number, uint8_t point_bit)
{
    int data_int = 0;                                                           // ��������
    int data_float = 0.0;                                                       // С������
    int data_temp[8];                                                           // �����ַ�����
    int data_temp_point[6];                                                     // С���ַ�����
    uint8_t bit = point_bit;                                                      // ת������λ��

    do
    {
        if(NULL == str)
        {
            break;
        }

        // ��ȡ��������
        data_int = (int)number;                                                 // ֱ��ǿ��ת��Ϊ int
        if(0 > number)                                                          // �ж�Դ�������������Ǹ���
        {
            *str ++ = '-';
        }
        else if(0.0 == number)                                                  // ����Ǹ� 0
        {
            *str ++ = '0';
            *str ++ = '.';
            *str = '0';
            break;
        }

        // ��ȡС������
        number = number - data_int;                                             // ��ȥ�������ּ���
        while(bit --)
        {
            number = number * 10;                                               // ����Ҫ��С��λ����ȡ����������
        }
        data_float = (int)number;                                               // ��ȡ�ⲿ����ֵ

        // ��������תΪ�ַ���
        bit = 0;
        do
        {
            data_temp[bit ++] = data_int % 10;                                  // ���������ֵ���д���ַ�������
            data_int /= 10;
        }while(0 != data_int);
        while(0 != bit)
        {
            *str ++ = (abs(data_temp[bit - 1]) + 0x30);                    // �ٵ��򽫵������ֵд���ַ��� �õ�������ֵ
            bit --;
        }

        // С������תΪ�ַ���
        if(point_bit != 0)
        {
            bit = 0;
            *str ++ = '.';
            if(0 == data_float)
            {
                *str = '0';
            }
            else
            {
                while(0 != point_bit)                                           // �ж���Чλ��
                {
                    data_temp_point[bit ++] = data_float % 10;                  // ����д���ַ�������
                    data_float /= 10;
                    point_bit --;
                }
                while(0 != bit)
                {
                    *str ++ = (abs(data_temp_point[bit - 1]) + 0x30);      // �ٵ��򽫵������ֵд���ַ��� �õ�������ֵ
                    bit --;
                }
            }
        }
    }while(0);
}