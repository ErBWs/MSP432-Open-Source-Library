/*!
 * @file    system_lint.c
 * @author  LX, Baohan
 * @date    2022/10/01
 */

#include "system.h"

/*
 * ʱ�ӣ�          Ĭ��ʱ��Դ         Ĭ��Ƶ��                    ����
 * MCLK             DCO              3MHZ           ��ʱ�ӣ���CPU�������ṩʱ��
 * HSMCLK           DCO              3MHZ           ��ϵͳ��ʱ�ӣ��������ṩʱ��Դ
 * SMCLK            DCO              3MHZ           ����ϵͳ��ʱ�ӣ��������ṩʱ��Դ
 * ACLK     LFXT(��REFOû�о���ʱ)   32.768kHz        ����ʱ�ӣ��������ṩʱ��
 * BCLK     LFXT(��REFOû�о���ʱ)   32.768kHz        ���ٺ�����ʱ�ӣ��ṩLPM����
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