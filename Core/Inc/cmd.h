#ifndef __CMD_H
#define __CMD_H

#include "main.h"
#include "gpio.h"
#include "MeasureR.h"
#include "MeasureLen.h"
#include "usart.h"
#include "user.h"

uint8_t readcmd(uint32_t timeout);
float handleLength();
float handleLoad(float length);

#endif