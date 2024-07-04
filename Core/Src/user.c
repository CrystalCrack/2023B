#include "user.h"

float Hz;
double len;
double hhz;
float r, R;
float v, V;
uint8_t i;

float length = NULL;

void setup()
{
    HAL_Delay(5000);
    if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
    {
        if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
        {
            printf("hadc1 error with HAL_ADCEx_Calibration_Start\r\n");
            Error_Handler();
        }
    }
    HAL_GPIO_WritePin(Switch_GPIO_Port, Switch_Pin, 0);
}

void loop()
{
    // for (i = 0; i < 100; i++)
    // {
    //     len += get_len(&Hz);
    //     hhz += Hz;
    // }
    // len /= 100;
    // hhz /= 100;
    // printf("%lfcm,%lfHz\n", len, hhz);
    // len = 0;
    // hhz = 0;
    for (i = 0; i < 100; i++)
    {
        r = getR(&v, 123.123);
        if (r == INFINITY)
        {
            printf("infinity");
            break;
        }
        V += v;
        R += r;
				HAL_Delay(10);
    }
    R /= 100;
    V/=100;
    printf("%fV, %f Ohm\n", V, R);
    R = 0;
    V = 0;
    HAL_Delay(10);
    // uint8_t cmd = readcmd(100);
    // switch(cmd){
    //     case DETECT_LENGTH:
    //         length = handleLength();
    //         break;
    //     case DETECT_LOAD:
    //         if(length!=NULL){
    //             handleLoad(length);
    //         }
    //         break;
    // }
}
