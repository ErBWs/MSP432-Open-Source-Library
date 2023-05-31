#include <driverlib.h>
#include "header.h"
#include "bsp/zf_device_icm20602.h"

int main(void)
{
    // System initialization
    SystemClockInit();

    // User initialization
    UART_Init(EUSCI_A0_BASE, 115200);
//    EnableUartInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
//    EnableUartInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    icm20602_init();
    ips114_init();
    ips114_show_string(0, 0, "hello");

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
        printf("icm20602: %d\n", icm20602_acc_x);
        Delay_ms(100);
    }
}