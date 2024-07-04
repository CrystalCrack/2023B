#include "MeasureR.h"

#define Rref 32.89
#define p1 1.0147
#define p2 -0.1415
#define p1_cable 0.0015
#define p2_cable 0.0621
uint16_t getADC()
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 50); // 等待转换完成，50为最大等待时间，单位为ms

    if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
    {
        uint16_t ADC_Value = HAL_ADC_GetValue(&hadc1);
        return ADC_Value;
    }
    else
    {
        return 0;
    }
}

float calcul_V(uint16_t adcvalue)
{
    float volt = 3.3 * adcvalue / 65536.0;
    return volt;
}

float getR(float *Volt, float length)
{
    uint16_t adcvalue = getADC();
    float V = calcul_V(adcvalue);
    *Volt = V;
    if ((3.3 - V) / 3.3 <= 1e-3)
    {
        return INFINITY;
    }
    float R = V * Rref / (3.3 - V);
    R = p1 * R + p2; // 线性修正
    R -= p1_cable * length + p2_cable;
    return R;
}