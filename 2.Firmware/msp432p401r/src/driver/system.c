/*!
 * Copyright (c) 2022, ErBW_s
 * All rights reserved.
 *
 * @author  Baohan
 */

#include "system.h"

/*!
 * @brief       Initialize the whole system
 *
 * @param       None
 * @return      None
 *
 * @note        Do not modify! Or you may permanently destroy the mcu
 */
void SystemClockInit()
{
    // Stop watchdog
    WDT_A_holdTimer();

    // Set DCO to 48MHz (need to change core voltage)
    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);

    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    // Enable FPU
    FPU_enableModule();
    FPU_enableLazyStacking();

    P4->DIR |= BIT3;
    P4->SEL0 |=BIT3;                        // Output MCLK
    P4->SEL1 &= ~(BIT3);
}