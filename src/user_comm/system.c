/*!
 * @file    system_lint.c
 * @author  LX, Baohan
 * @date    2022/10/01
 */

#include "system.h"

void SystemClockInit()
{
    /* Stop Watchdog  */
    WDT_A_holdTimer();

    /* Setting DCO to 48MHz (upping Vcore) */
    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);

    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    FPU_enableModule();
    FPU_enableLazyStacking();
}