/*************************************************
Copyright  (c)Guoxinchangtian Technologies Co., Ltd. 2008-2019. All rights reserved.
File name: sts30.c
Author:      Version:   Date:2019.10.10
Description: 温度传感器的功能函数
Others:
History:

1. Date:
Author:
Modification:
*************************************************/
#include "sts30.h"

extern I2C_HandleTypeDef hi2c1;

float Get_Temperature(void)
{
    uint8_t H_VALUE, L_VALUE, CRC_VALUE;
    uint16_t T_VALUE; //转换完成的数字值
    float temperature;//转换完成的温度值
    uint8_t ucData[2];
    uint8_t reData[3];
    ucData[0] = 0x24;
    ucData[1] = 0x0b;
    HAL_I2C_Master_Transmit(&hi2c1,(0x4A << 1), ucData, 2, 0xffff);
    HAL_Delay(2);
    HAL_I2C_Master_Receive(&hi2c1, (0x4A << 1 | 1), reData, 0, 0xffff);
    HAL_Delay(2);
    HAL_I2C_Master_Receive(&hi2c1, (0x4A << 1 | 1), reData, 3, 0xffff);
   
    H_VALUE = reData[0];
    L_VALUE = reData[1];
    CRC_VALUE = reData[2];
    if (CRC_VALUE)
    {
        ;
    }
    T_VALUE = H_VALUE << 8 | L_VALUE;
    temperature = -45 + 175.0 * T_VALUE / 65535;

    return (temperature);
}




