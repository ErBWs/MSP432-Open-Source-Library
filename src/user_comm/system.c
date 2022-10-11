/*!
 * @file    system_lint.c
 * @author  LX, Baohan
 * @date    2022/10/01
 */

#include "system.h"

void SystemClockInit()
{
    // static volatile uint32_t aclk, mclk, smclk, hsmclk, bclk;
    /* Stop Watchdog  */
    WDT_A_holdTimer();

    /* Setting DCO to 48MHz (upping Vcore) */
    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);

    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    // aclk = CS_getACLK();
    // mclk = CS_getMCLK();
    // smclk = CS_getSMCLK();
    // hsmclk = CS_getHSMCLK();
    // bclk = CS_getBCLK();

    FPU_enableModule();
    FPU_enableLazyStacking();
}