#include "header.h"
#define UART EUSCI_A0_BASE

void vcan_sendware(void *wareaddr, uint32_t waresize)//山外波形函数
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试 使用的前命令
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试 使用的后命令

    UART_PutNChar(UART, cmdf, sizeof(cmdf));    //先发送前命令 注意设置好串口号
    UART_PutNChar(UART, (uint8_t *)wareaddr, waresize);    //发送数据
    UART_PutNChar(UART, cmdr, sizeof(cmdr));    //发送后命令

}
