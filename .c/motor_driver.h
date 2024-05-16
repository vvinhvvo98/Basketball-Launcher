/**
  ******************************************************************************
  * @file            motor_driver.h
  * @brief           Header for motor_driver.c file.
  *                  This file contains the common defines of the application.
  ******************************************************************************
  */

#ifndef INC_MOTOR_DRIVER_H_
#define INC_MOTOR_DRIVER_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"

/**
 * @brief Struct representing a motor driver.
 */
typedef struct
{
    TIM_HandleTypeDef* timer;   /**< Timer handle for PWM control. */
    uint32_t channel1;          /**< Timer channel 1 for PWM control. */
    uint32_t channel2;          /**< Timer channel 2 for PWM control. */
    int32_t duty;               /**< Duty cycle of the PWM signal. */
    int32_t CCR;                /**< Capture/Compare Register value. */
} MotorX;

/**
 * @brief Initializes the motor driver.
 * 
 * @param motx Pointer to the MotorX structure.
 * @param timer Pointer to the timer handle.
 * @param channel1 Timer channel 1 for PWM control.
 * @param channel2 Timer channel 2 for PWM control.
 * @param CCR Capture/Compare Register value.
 */
void motor_init(MotorX* motx, TIM_HandleTypeDef* timer, uint32_t channel1, uint32_t channel2, int32_t CCR);

/**
 * @brief Enables the motor driver.
 * 
 * @param motx Pointer to the MotorX structure.
 */
void motor_enable(MotorX* motx);

/**
 * @brief Sets the duty cycle of the motor driver.
 * 
 * @param motx Pointer to the MotorX structure.
 * @param duty Desired duty cycle.
 */
void motor_setduty(MotorX* motx, int32_t duty);

/**
 * @brief Disables the motor driver.
 * 
 * @param motx Pointer to the MotorX structure.
 */
void motor_disable(MotorX* motx);

#endif /* INC_MOTOR_DRIVER_H_ */
