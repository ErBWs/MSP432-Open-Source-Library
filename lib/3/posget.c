/*
 * posget.c
 *
 *  Created on: 2022��4��30��
 *      Author: Breeze
 */

#include "posget.h"
#include "math.h"
#define icm_gyro_x mpu_gyro_x
#define icm_gyro_y mpu_gyro_y
#define icm_gyro_z mpu_gyro_z

#define icm_acc_x mpu_acc_x
#define icm_acc_y mpu_acc_y
#define icm_acc_z mpu_acc_z
struct
{
    int16 Xdata;
    int16 Ydata;
    int16 Zdata;
} GyroOffset;
void gyroOffsetInit(void)
{
    GyroOffset.Xdata = 0;
    GyroOffset.Ydata = 0;
    GyroOffset.Zdata = 0;
    for (uint16 i = 0; i < 100; ++i)
    {
        get_gyro(); // ��ȡ�����ǽ��ٶ�
        GyroOffset.Xdata += icm_gyro_x;
        GyroOffset.Ydata += icm_gyro_y;
        GyroOffset.Zdata += icm_gyro_z;
        delay_ms(5); // ��� 1Khz
    }

    GyroOffset.Xdata /= 100;
    GyroOffset.Ydata /= 100;
    GyroOffset.Zdata /= 100;
}

struct icm_param_t icm_data;
void icmGetValues(void)
{
    float alpha = 0.3;
    get_accdata();
    get_gyro();
    //һ�׵�ͨ�˲�����λg
    icm_data.acc_x = (((float)icm_acc_x) * alpha) / 4096 + icm_data.acc_x * (1 - alpha);
    icm_data.acc_y = (((float)icm_acc_y) * alpha) / 4096 + icm_data.acc_y * (1 - alpha);
    icm_data.acc_z = (((float)icm_acc_z) * alpha) / 4096 + icm_data.acc_z * (1 - alpha);

    //! �����ǽ��ٶȱ���ת��Ϊ�����ƽ��ٶ�: deg/s -> rad/s
    icm_data.gyro_x = ((float)icm_gyro_x - GyroOffset.Xdata) * PI / 180 / 16.4f;
    icm_data.gyro_y = ((float)icm_gyro_y - GyroOffset.Ydata) * PI / 180 / 16.4f;
    icm_data.gyro_z = ((float)icm_gyro_z - GyroOffset.Zdata) * PI / 180 / 16.4f;
}

float I_ex, I_ey, I_ez;                      // ������
struct quater_param_t Q_info = {1, 0, 0, 0}; // ��Ԫ����ʼ��
struct euler_param_t eulerAngle;             // ŷ����
float roll_get;
// float icm_kp= 0.17;    // ���ٶȼƵ��������ʱ�������
// float icm_ki= 0.004;   // �������������ʵĻ�������
// float icm_kp= 0.97;    // ���ٶȼƵ��������ʱ�������
// float icm_ki= 0.04;   // �������������ʵĻ�������
float icm_kp = 0.5;    // ���ٶȼƵ��������ʱ�������
float icm_ki = 0.0001; // �������������ʵĻ�������
void icmAHRSupdate(struct icm_param_t *icm)
{
    float halfT = 0.5 * delta_T; // ��������һ��
    float vx, vy, vz;            // ��ǰ��̬��������������������ϵķ���
    float ex, ey, ez;            // ��ǰ���ټƲ�õ��������ٶ��������ϵķ������õ�ǰ��̬��������������������ϵķ��������

    float q0 = Q_info.q0; //��Ԫ��
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;

    float q0q0 = q0 * q0; //����ˣ������������
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;

    eulerAngle.pitch = asinf(2 * q0 * q2 - 2 * q1 * q3) * 180 / PI;
    eulerAngle.roll = atan2f(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 180 / PI;
    eulerAngle.yaw = atan2f(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 180 / PI;

    roll_get = ((float)(int)((eulerAngle.roll + 0.5) * 100)) / 100.;
    // ������ֹ״̬Ϊ-g ����������
    if (icm->acc_x * icm->acc_y * icm->acc_z == 0) // �Ӽƴ�����������״̬ʱ(��ʱg = 0)��������̬���㣬��Ϊ�������ĸ���������
        return;

    // �Լ��ٶ����ݽ��й�һ�� �õ���λ���ٶ� (a^b -> ��������ϵ�µļ��ٶ�)
    float norm = myRsqrt(icm->acc_x * icm->acc_x + icm->acc_y * icm->acc_y + icm->acc_z * icm->acc_z);
    icm->acc_x = icm->acc_x * norm;
    icm->acc_y = icm->acc_y * norm;
    icm->acc_z = icm->acc_z * norm;

    // ��������ϵ���������������ϵķ���
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;

    // g^b �� a^b ��������ˣ��õ������ǵ�У����������e��ϵ��
    ex = icm->acc_y * vz - icm->acc_z * vy;
    ey = icm->acc_z * vx - icm->acc_x * vz;
    ez = icm->acc_x * vy - icm->acc_y * vx;

    // ����ۼ�
    I_ex += halfT * ex;
    I_ey += halfT * ey;
    I_ez += halfT * ez;

    // ʹ��PI�������������������(������Ư�����)
    icm->gyro_x = icm->gyro_x + icm_kp * ex + icm_ki * I_ex;
    icm->gyro_y = icm->gyro_y + icm_kp * ey + icm_ki * I_ey;
    icm->gyro_z = icm->gyro_z + icm_kp * ez + icm_ki * I_ez;

    // һ����������������Ԫ��΢�ַ��̣�����halfTΪ�������ڵ�1/2��gx gy gzΪbϵ�����ǽ��ٶȡ�
    q0 = q0 + (-q1 * icm->gyro_x - q2 * icm->gyro_y - q3 * icm->gyro_z) * halfT;
    q1 = q1 + (q0 * icm->gyro_x + q2 * icm->gyro_z - q3 * icm->gyro_y) * halfT;
    q2 = q2 + (q0 * icm->gyro_y - q1 * icm->gyro_z + q3 * icm->gyro_x) * halfT;
    q3 = q3 + (q0 * icm->gyro_z + q1 * icm->gyro_y - q2 * icm->gyro_x) * halfT;

    // ��λ����Ԫ���ڿռ���תʱ�������죬������ת�Ƕȣ������㷨�������Դ�����������任
    norm = myRsqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    Q_info.q0 = q0 * norm;
    Q_info.q1 = q1 * norm;
    Q_info.q2 = q2 * norm;
    Q_info.q3 = q3 * norm; // ��ȫ�ֱ�����¼��һ�μ������Ԫ��ֵ
}

float myRsqrt(float num)
{
    float halfx = 0.5f * num;
    float y = num;
    long i = *(long *)&y;
    i = 0x5f375a86 - (i >> 1);

    y = *(float *)&i;
    y = y * (1.5f - (halfx * y * y));
    y = y * (1.5f - (halfx * y * y));

    return y;
}
float filter_first(float data)
{
    static float data_out;
    data_out = data_out * 0.9;
    data_out = data_out + data * 0.1;
    return data_out;
}
void get_pos(void)
{
    icmGetValues();
    icmAHRSupdate(&icm_data);
}