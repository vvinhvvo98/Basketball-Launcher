/*
 * d4215.h
 *
 *  Created on: May 1, 2024
 *      Author: vvinh
 */

#ifndef INC_D4215_H_
#define INC_D4215_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct
{
	TIM_HandleTypeDef* timer;
    uint32_t channel;
    int32_t speed;
} D4215X;

// Prototype for motor object "method"
void D4215_init(D4215X* bldcx, TIM_HandleTypeDef* timer, uint32_t channel);
void D4215_set (D4215X* bldcx, int32_t speed); // speed = [5 10]


#endif /* INC_D4215_H_ */
