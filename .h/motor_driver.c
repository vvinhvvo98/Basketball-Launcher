/**
 * @file motor_driver.c
 * @brief Implementation of  DC motor driver functions.
 * 
 *  Created on: May 3, 2024
 *  Author: vvinh
 */
#include "motor_driver.h"
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Initializes the motor configuration.
 * 
 * @param motx Pointer to the MotorX structure.
 * @param timer Pointer to the timer handle.
 * @param channel1 Timer channel 1 for PWM control.
 * @param channel2 Timer channel 2 for PWM control.
 * @param CCR Capture/Compare Register value.
 */
void motor_init(MotorX* motx, TIM_HandleTypeDef* timer, uint32_t channel1, uint32_t channel2, int32_t CCR) {
    motx->timer = timer;
    motx->channel1 = channel1;
    motx->channel2 = channel2;
    motx->CCR = CCR;
    motx->duty = 0;
    HAL_TIM_PWM_Start(motx->timer, motx->channel1);
    HAL_TIM_PWM_Start(motx->timer, motx->channel2);
}

/**
 * @brief Enables the motor by starting PWM signal generation.
 * 
 * @param motx Pointer to the MotorX structure.
 */
void motor_enable(MotorX* motx) {
    __HAL_TIM_SET_COMPARE(motx->timer, motx->channel1, 100 * motx->CCR);
    __HAL_TIM_SET_COMPARE(motx->timer, motx->channel2, 100 * motx->CCR);
}

/**
 * @brief Sets the duty cycle of the motor.
 * 
 * @param motx Pointer to the MotorX structure.
 * @param duty Desired duty cycle.
 */
void motor_setduty(MotorX* motx, int32_t duty) {
    motx->duty = duty;
    if (duty >= 0) {
        __HAL_TIM_SET_COMPARE(motx->timer, motx->channel1, duty * motx->CCR);
        __HAL_TIM_SET_COMPARE(motx->timer, motx->channel2, 0);
    }
    else if (duty < 0) {
        __HAL_TIM_SET_COMPARE(motx->timer, motx->channel1, 0);
        __HAL_TIM_SET_COMPARE(motx->timer, motx->channel2, -duty * motx->CCR);
    }
}

/**
 * @brief Disables the motor by stopping PWM signal generation.
 * 
 * @param motx Pointer to the MotorX structure.
 */
void motor_disable(MotorX* motx) {
    __HAL_TIM_SET_COMPARE(motx->timer, motx->channel1, 0);
    __HAL_TIM_SET_COMPARE(motx->timer, motx->channel2, 0);
}

