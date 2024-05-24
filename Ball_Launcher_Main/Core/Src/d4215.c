/**
  ******************************************************************************
  * @file            d4215.c
  * @brief           Source file for D4215 motor operations.
  *                  This file contains the implementation of the functions for
  *                  initializing and controlling a D4215 motor.
  ******************************************************************************
  * Created on: May 1, 2024
  *
  * Author: vvinh
  */
#include "d4215.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

/**
  * @brief Initializes the D4215 motor with the specified timer and channel.
  *
  * @param bldcx Pointer to the D4215X structure
  * @param timer Timer handle
  * @param channel Timer channel
  */
void D4215_init(D4215X* bldcx, TIM_HandleTypeDef* timer, uint32_t channel) {
    bldcx->timer = timer;
    bldcx->channel = channel;
    bldcx->speed = 0;
    HAL_TIM_PWM_Start(bldcx->timer, bldcx->channel); /**< Start PWM for the specified timer and channel */
}

/**
  * @brief Sets the speed of the D4215 motor.
  *
  * @param bldcx Pointer to the D4215X structure
  * @param spd Speed of the motor (range: 5 to 10)
  */
void D4215_set(D4215X* bldcx, int32_t spd) {
	float speed = 0.05 * spd + 5; /**< Calculate the duty cycle based on the input speed */
    bldcx->speed = speed;
    __HAL_TIM_SET_COMPARE(bldcx->timer, bldcx->channel, speed * 200); /**< Set the duty cycle for the PWM */
}
