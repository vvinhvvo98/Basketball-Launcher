/**
 * @file D4215.c
 * @brief Implementation of hobby bldc motor driver functions.
 * 
 *  Created on: May 3, 2024
 *  Author: vvinh
 */

#include "D4215.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Initializes the D4215 motor configuration.
 * 
 * @param bldcx Pointer to the D4215x structure.
 * @param timer Pointer to the timer handle.
 * @param channel Timer channel for PWM control.
 */
void D4215_init(D4215x* bldcx, TIM_HandleTypeDef* timer, uint32_t channel) {
    bldcx->timer = timer;
    bldcx->channel = channel;
    bldcx->speed = 0;
    HAL_TIM_PWM_Start(bldcx->timer, bldcx->channel);
}

/**
 * @brief Sets the duty cycle of the D4215 motor.
 * 
 * @param bldcx Pointer to the D4215x structure.
 * @param spd Desired speed of the motor. Speed range is [5, 10].
 */
void D4215_set(D4215x* bldcx, int32_t spd) {
    double speed = 0.05 * spd + 5;
    bldcx->speed = speed;
    __HAL_TIM_SET_COMPARE(bldcx->timer, bldcx->channel, speed * 5000);
}