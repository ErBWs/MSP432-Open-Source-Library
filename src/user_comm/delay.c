/*!
 * @file    delay.c
 * @author  zf, Baohan
 * @date    2022/05/25
 */

#include "delay.h"

/*!
 * @brief       Delay function
 *
 * @param       time        Unit is ns
 * @param       num         Number of delays required
 * @return      None
 *
 * @note        This function is for internal usage, user call please check macro in delay.h
 */
void SystemDelay (uint32_t time, uint32_t num)
{
    while(num --)
    {
        SysTick->CTRL	= 0x00;
        SysTick->LOAD	= (sysClk / 1000000 * time / 1000);
        SysTick->VAL	= 0x00;
        SysTick->CTRL	=	SysTick_CTRL_CLKSOURCE_Msk |                        // Select core clk
                              SysTick_CTRL_ENABLE_Msk;                          // Enable SysTick
        while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    }
}
// void delay_us(uint32_t x)
// {
//   for (uint32_t i = 0; i < (x); i++)
//     for (uint32_t j = 8; j > 0; j--)
//       ;
// }
// void delay_ms(uint32_t x)
// {
//   for (uint32_t i = 0; i < (x); i++)
//     for (uint32_t j = 8026; j > 0; j--)
//       ;
// }