/*!
 * Copyright (c) 2023, ErBW_s
 * All rights reserved.
 * 
 * @author  Baohan
 *
 * @note    VOFA+ in macOS have some issue with FireWater,
 *          to use FireWater you need to remain 'sample: '
 *          for it to successfully analyze data.
 */

#include "vofa.h"

float vofaData[CHANNEL_NUM] = {0};

/*!
 * @brief   Vofa send data using JustFloat
 *
 * @param   void
 * @return  void
 */
void VofaSendFrame()
{
    unsigned char vofaTail[4] = {0x00, 0x00, 0x80, 0x7F};

    // More steps for Big-Endian
    if (CheckEndianness() == Big_Endian)
    {
        vofaTail[0] = 0x7F;
        vofaTail[1] = 0x80;
        vofaTail[2] = 0x00;
        vofaTail[3] = 0x00;

        float temp;

        for (int i = 0; i < CHANNEL_NUM * sizeof(float); i += 2)
        {
            temp = ((uint8_t *) vofaData)[i];
            ((uint8_t *) vofaData)[i] = ((uint8_t *) vofaData)[i + 1];
            ((uint8_t *) vofaData)[i + 1] = (uint8_t) temp;
        }
    }

    UART_Send8BitArray(VOFA_UART, (uint8_t *) vofaData, CHANNEL_NUM * sizeof(float));
    UART_Send8BitArray(VOFA_UART, (uint8_t *) vofaTail, 4);
}