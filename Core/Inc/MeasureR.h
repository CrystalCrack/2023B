#ifndef __MEASURER_H
#define __MEASURER_H
#include "main.h"
#include "adc.h"

uint16_t getADC();
float calcul_V(uint16_t adcvalue);
float getR(float *Volt, float length);

#endif