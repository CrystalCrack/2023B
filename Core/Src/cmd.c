#include "cmd.h"

#define S(x) HAL_GPIO_WritePin(Switch_GPIO_Port, Switch_Pin, x);

uint8_t Readcmd(uint32_t timeout)
{
    uint8_t cmd;
    HAL_UART_Receive(&huart1, &cmd, 1, timeout);
    switch (cmd)
    {
    case 0x30:
        return DETECT_LENGTH;
        break;
    case 0x31:
        return DETECT_LOAD;
        break;
    }
    return 0;
}

// 串口屏显示
void show(const char *objname, const char *txt)
{
    printf("%s.txt=\"%s\"\xff\xff\xff", objname, txt);
}

void switchMode(char m)
{
    switch (m)
    {
    case 'L':
    case 'C':
        S(1);
        break;
    case 'R':
        S(0);
        break;
    }
}

float handleLength()
{
    show("status", "DETECTING");
    switchMode('L');
    float length = get_len();
    char lenbuf[10];
    sprintf(lenbuf, "%.2f", length);
    show("status", "READY");
    show("length", lenbuf);
    return length;
}

float handleLoad(float length)
{
    show("status", "DETECTING");
    switchMode('R'); // 先检测电阻
    float R = getR(0x33, length);
    if (R == INFINITY)
    { // 开路
        show("status", "READY");
        show("type", "Capacitive");
        switchMode('C');
    }
    else
    {
        show("status", "READY");
        show("type", "Resistive");
        char Rbuf[10];
        sprintf(Rbuf, "%.2f", R);
        show("value", Rbuf);
    }
    return 1;
}