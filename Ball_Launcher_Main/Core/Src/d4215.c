/*
 * d4215.c
 *
 *  Created on: May 1, 2024
 *      Author: vvinh
 */

#include "d4215.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

// Initialize motor configuration
void D4215_init(D4215X* bldcx, TIM_HandleTypeDef* timer, uint32_t channel) {
    bldcx->timer = timer;
    bldcx->channel = channel;
    bldcx->speed = 0;
    HAL_TIM_PWM_Start(bldcx->timer, bldcx->channel);
}

// Set the duty cycle of the motor
void D4215_set(D4215X* bldcx, int32_t spd) {
	float speed = 0.05 * spd + 5;
    bldcx->speed = speed;
    __HAL_TIM_SET_COMPARE(bldcx->timer, bldcx->channel, speed * 200);
}
