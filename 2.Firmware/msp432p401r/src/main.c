#include <driverlib.h>
#include "header.h"

int main(void)
{
    // System initialization
    SystemClockInit();

    // User initialization
    UART_Init(EUSCI_A0_BASE, 115200);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    icm20602_init();
//    bmi270_init();
//    ips114_init();
//    ips114_show_string(0, 0, "EasyUI");

    // Enable global interrupt
    Interrupt_enableMaster();
    float temp = 0;

    while (1)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
//        vofaData[0] = sinf(temp);
//        temp += 0.1f;
//        VofaSendFrame();
//        printf("sin: %f\n", sinf(temp));
        icm20602_get_acc();
        printf("icm20602accx: %d\n", icm20602_acc_x);
//        bmi270_get_acc();
//        printf("bmiaccx: %d\n", bmi270_acc_x);
        Delay_ms(100);
    }
}