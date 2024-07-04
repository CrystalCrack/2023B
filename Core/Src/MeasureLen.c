#include "MeasureLen.h"
#include "main.h"
#include "tim.h"

#define a 742628.583441790310
#define b -4.626668230517
#define c -2.461134733573

uint8_t capture_state = 0;
uint32_t capture_buf[3];

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim2)
    {
        switch (capture_state)
        {
        case 1: // 捕获到上升沿
            capture_buf[0] = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_ICPOLARITY_FALLING);
            capture_state++;
            break;
        case 2: // 捕获到下降沿
            capture_buf[1] = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_ICPOLARITY_RISING);
            capture_state++;
            break;
        case 3: // 再次捕获到上升沿
            capture_buf[2] = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
            capture_state++;
            break;
        }
    }
}

float get_osc_freq()
{
    uint32_t cnts;
    float Hz;
    __HAL_TIM_SetCounter(&htim2, 0);
    __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_ICPOLARITY_RISING);
    __HAL_TIM_SET_PRESCALER(&htim2, 47); // 5MHz
    HAL_TIM_GenerateEvent(&htim2, TIM_EventSource_Update);
    capture_state++;
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
    while (capture_state < 4)
        ;
    HAL_TIM_IC_Stop(&htim2, TIM_CHANNEL_2);
    capture_state = 0;
    cnts = capture_buf[2] - capture_buf[0];
    Hz = 5000000.0 / cnts;
    return Hz;
}

float calcul_len(float Hz)
{
    return a / (Hz + b) + c;
}

float get_len(float *Hzin)
{
    float Hz = get_osc_freq();
    float length = calcul_len(Hz);
    *Hzin = Hz;
    return length;
}