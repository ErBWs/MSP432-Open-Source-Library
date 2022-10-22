/*!
 * @file    user_spi.h
 * @author  Baohan
 * @date    2022/10/12
 */

#ifndef _USER_SPI_H
#define _USER_SPI_H

#include <driverlib.h>
#include "header.h"

typedef enum
{
    SPI_A0_CLK_P11      = 0x0011,       // 0x 0[eUSCIA0] 0[AF0] 1[PORT1] 1[PIN1]
    SPI_A1_CLK_P21      = 0x1021,       // 0x 1[eUSCIA1] 0[AF0] 2[PORT2] 1[PIN1]
    SPI_A2_CLK_P31      = 0x2031,       // 0x 2[eUSCIA2] 0[AF0] 3[PORT3] 1[PIN1]
    SPI_A3_CLK_P95      = 0x3095,       // 0x 3[eUSCIA3] 0[AF0] 9[PORT9] 5[PIN5]

    SPI_B0_CLK_P15      = 0x4015,       // 0x 4[eUSCIB0] 0[AF0] 1[PORT1] 5[PIN5]
    SPI_B1_CLK_P63      = 0x5063,       // 0x 5[eUSCIB1] 0[AF0] 6[PORT6] 3[PIN3]
    SPI_B2_CLK_P35      = 0x6035,       // 0x 6[eUSCIB2] 0[AF0] 3[PORT3] 5[PIN5]
    SPI_B3_CLK_P101     = 0x70A1,       // 0x 7[eUSCIB3] 0[AF0] A[PORT10] 1[PIN1]
}SpiClkPinEnum;

typedef enum
{
    SPI_A0_MOSI_P13     = 0x0013,       // 0x 0[eUSCIA0] 0[AF0] 1[PORT1] 3[PIN3]
    SPI_A1_MOSI_P23     = 0x1023,       // 0x 1[eUSCIA1] 0[AF0] 2[PORT2] 3[PIN3]
    SPI_A2_MOSI_P33     = 0x2033,       // 0x 2[eUSCIA2] 0[AF0] 3[PORT3] 3[PIN3]
    SPI_A3_MOSI_P97     = 0x3097,       // 0x 3[eUSCIA3] 0[AF0] 9[PORT9] 7[PIN7]

    SPI_B0_MOSI_P16     = 0x4016,       // 0x 4[eUSCIB0] 0[AF0] 1[PORT1] 6[PIN6]
    SPI_B1_MOSI_P64     = 0x5064,       // 0x 5[eUSCIB1] 0[AF0] 6[PORT6] 4[PIN4]
    SPI_B2_MOSI_P36     = 0x6036,       // 0x 6[eUSCIB2] 0[AF0] 3[PORT3] 6[PIN6]
    SPI_B3_MOSI_P66     = 0x7166,       // 0x 7[eUSCIB3] 1[AF1] 6[PORT6] 6[PIN6]
    SPI_B3_MOSI_P102    = 0x70A2,       // 0x 7[eUSCIB3] 0[AF0] A[PORT10] 2[PIN2]
}SpiMosiPinEnum;

typedef enum
{
    SPI_MISO_NULL       = 0xFFFF,       // Fill with this if not using hardware miso

    SPI_A0_MISO_P12     = 0x0012,       // 0x 0[eUSCIA0] 0[AF0] 1[PORT1] 2[PIN2]
    SPI_A1_MISO_P22     = 0x1022,       // 0x 1[eUSCIA1] 0[AF0] 2[PORT2] 2[PIN2]
    SPI_A2_MISO_P32     = 0x2032,       // 0x 2[eUSCIA2] 0[AF0] 3[PORT3] 2[PIN2]
    SPI_A3_MISO_P96     = 0x3096,       // 0x 3[eUSCIA3] 0[AF0] 9[PORT9] 6[PIN6]

    SPI_B0_MISO_P17     = 0x4017,       // 0x 4[eUSCIB0] 0[AF0] 1[PORT1] 7[PIN7]
    SPI_B1_MISO_P65     = 0x5065,       // 0x 5[eUSCIB1] 0[AF0] 6[PORT6] 5[PIN5]
    SPI_B2_MISO_P37     = 0x6037,       // 0x 6[eUSCIB2] 0[AF0] 3[PORT3] 7[PIN7]
    SPI_B3_MISO_P67     = 0x7167,       // 0x 7[eUSCIB3] 1[AF1] 6[PORT6] 7[PIN7]
    SPI_B3_MISO_P103    = 0x70A3,       // 0x 7[eUSCIB3] 0[AF0] A[PORT10] 3[PIN3]
}SpiMisoPinEnum;

typedef enum
{
    SPI_CS_NULL         = 0xFFFF,       // Fill with this if not using hardware cs

    SPI_A0_CS_P10       = 0x0010,       // 0x 0[eUSCIA0] 0[AF0] 1[PORT1] 0[PIN0]
    SPI_A1_CS_P20       = 0x1020,       // 0x 1[eUSCIA1] 0[AF0] 2[PORT2] 0[PIN0]
    SPI_A2_CS_P30       = 0x2030,       // 0x 2[eUSCIA2] 0[AF0] 3[PORT3] 0[PIN0]
    SPI_A3_CS_P94       = 0x3094,       // 0x 3[eUSCIA3] 0[AF0] 9[PORT9] 4[PIN4]

    SPI_B0_CS_P14       = 0x4014,       // 0x 4[eUSCIB0] 0[AF0] 1[PORT1] 4[PIN4]
    SPI_B1_CS_P62       = 0x5062,       // 0x 5[eUSCIB1] 0[AF0] 6[PORT6] 2[PIN2]
    SPI_B2_CS_P34       = 0x6034,       // 0x 6[eUSCIB2] 0[AF0] 3[PORT3] 4[PIN4]
    SPI_B3_CS_P80       = 0x7080,       // 0x 7[eUSCIB3] 0[AF0] 8[PORT8] 0[PIN0]
    SPI_B3_CS_P100      = 0x70A0,       // 0x 7[eUSCIB3] 0[AF0] A[PORT10] 0[PIN0]
}SpiCsPinEnum;

typedef enum
{
    SPI_MODE0,          // Low pin level while inactive and data captured on SCK 1st edge, changed on 2nd edge
    SPI_MODE1,          // Low pin level while inactive and data changed on SCK 1st edge, captured on 2nd edge
    SPI_MODE2,          // High pin level while inactive and data captured on SCK 1st edge, changed on 2nd edge
    SPI_MODE3,          // High pin level while inactive and data changed on SCK 1st edge, captured on 2nd edge
}SpiModeEnum;

typedef enum
{
    SPI_CS_MODE_NULL,   // Fill with this if not using hardware cs

    SPI_CS_MODE0,       // CS high pin level activate
    SPI_CS_MODE1,       // CS low pin level activate
}SpiCsModeEnum;

void SpiInit(SpiModeEnum _mode, SpiCsModeEnum _csMode, uint32_t baud, SpiClkPinEnum _clkPin, SpiMosiPinEnum _mosiPin, SpiMisoPinEnum _misoPin, SpiCsPinEnum _csPin);

#endif
