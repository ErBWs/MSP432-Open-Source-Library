/*!
 * @file    system_lint.c
 * @author  LX, Baohan
 * @date    2022/10/01
 */

#include "system.h"

/*
 * 时钟：          默认时钟源         默认频率                    描述
 * MCLK             DCO              3MHZ           主时钟，向CPU和外设提供时钟
 * HSMCLK           DCO              3MHZ           子系统主时钟，向外设提供时钟源
 * SMCLK            DCO              3MHZ           低速系统主时钟，向外设提供时钟源
 * ACLK     LFXT(或REFO没有晶振时)   32.768kHz        辅助时钟，向外设提供时钟
 * BCLK     LFXT(或REFO没有晶振时)   32.768kHz        低速后配域时钟，提供LPM外设
 */

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