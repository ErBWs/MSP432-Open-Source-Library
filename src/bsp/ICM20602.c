#include "ICM20602.h" 

int16_t icm_gyro_x, icm_gyro_y, icm_gyro_z;
int16_t icm_acc_x, icm_acc_y, icm_acc_z;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602自检函数
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void icm20602_self1_check(void)
{
    uint8_t dat = 0;
    while (0x12 != dat) //读取ICM20602 ID
    {
        dat = simiic_read_reg(ICM20602_DEV_ADDR, ICM20602_WHO_AM_I, SIMIIC);
        Delay_ms(10);
        //卡在这里原因有以下几点
        // 1 ICM20602坏了，如果是新的这样的概率极低
        // 2 接线错误或者没有接好
        // 3 可能你需要外接上拉电阻，上拉到3.3V
        // 4 可能没有调用模拟IIC的初始化函数
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化ICM20602
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void icm20602_init(void)
{
    simiic_init();
    Delay_ms(10); //上电延时

    //检测
    icm20602_self1_check();

    //复位
    simiic_write_reg(ICM20602_DEV_ADDR, ICM20602_PWR_MGMT_1, 0x80); //复位设备
    Delay_ms(2);                                                    //延时
    while (0x80 & simiic_read_reg(ICM20602_DEV_ADDR, ICM20602_PWR_MGMT_1, SIMIIC))
        ; //等待复位完成

    //配置参数
    simiic_write_reg(ICM20602_DEV_ADDR, ICM20602_PWR_MGMT_1, 0x01);     //时钟设置
    simiic_write_reg(ICM20602_DEV_ADDR, ICM20602_PWR_MGMT_2, 0x00);     //开启陀螺仪和加速度计
    simiic_write_reg(ICM20602_DEV_ADDR, ICM20602_CONFIG, 0x01);         // 176HZ 1KHZ
    simiic_write_reg(ICM20602_DEV_ADDR, ICM20602_SMPLRT_DIV, 0x07);     //采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    simiic_write_reg(ICM20602_DEV_ADDR, ICM20602_GYRO_CONFIG, 0x18);    //±2000 dps
    simiic_write_reg(ICM20602_DEV_ADDR, ICM20602_ACCEL_CONFIG, 0x10);   //±8g
    simiic_write_reg(ICM20602_DEV_ADDR, ICM20602_ACCEL_CONFIG_2, 0x03); // Average 4 samples   44.8HZ   //0x23 Average 16 samples
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602加速度计数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_accdata(void)
{
    uint8_t dat[6];

    simiic_read_regs(ICM20602_DEV_ADDR, ICM20602_ACCEL_XOUT_H, dat, 6, SIMIIC);
    icm_acc_x = (int16_t)(((uint16_t)dat[0] << 8 | dat[1]));
    icm_acc_y = (int16_t)(((uint16_t)dat[2] << 8 | dat[3]));
    icm_acc_z = (int16_t)(((uint16_t)dat[4] << 8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602陀螺仪数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_gyro(void)
{
    uint8_t dat[6];

    simiic_read_regs(ICM20602_DEV_ADDR, ICM20602_GYRO_XOUT_H, dat, 6, SIMIIC);
    icm_gyro_x = (int16_t)(((uint16_t)dat[0] << 8 | dat[1]));
    icm_gyro_y = (int16_t)(((uint16_t)dat[2] << 8 | dat[3]));
    icm_gyro_z = (int16_t)(((uint16_t)dat[4] << 8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  以上函数是使用软件IIC通信，相比较硬件IIC，软件IIC引脚更加灵活，可以使用任意普通IO
//-------------------------------------------------------------------------------------------------------------------
