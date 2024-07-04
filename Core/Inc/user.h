#ifndef __USER_H
#define __USER_H
#include "main.h"
#include "MeasureLen.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "MeasureR.h"
#include "adc.h"
#include "cmd.h"

#define DETECT_LENGTH 30
#define DETECT_LOAD 31

void setup();
void loop();

#endif