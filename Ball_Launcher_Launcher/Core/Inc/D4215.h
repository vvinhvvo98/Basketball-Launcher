/**
  ******************************************************************************
  * @file            D4215.h
  * @brief           Header for D4215.c file.
  *                  This file contains the common defines of the application.
  ******************************************************************************
  */

#ifndef INC_D4215_H_
#define INC_D4215_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
 * @brief Struct representing a D4215 motor driver.
 */
typedef struct
{
    TIM_HandleTypeDef* timer;   /**< Timer handle for PWM control. */
    uint32_t channel;           /**< Timer channel for PWM control. */
    int32_t speed;              /**< Speed of the motor. */
} D4215x;

/**
 * @brief Initializes the D4215 motor driver.
 * 
 * @param bldcx Pointer to the D4215x structure.
 * @param timer Pointer to the timer handle.
 * @param channel Timer channel for PWM control.
 */
void D4215_init(D4215x* bldcx, TIM_HandleTypeDef* timer, uint32_t channel);

/**
 * @brief Sets the speed of the D4215 motor.
 * 
 * @param bldcx Pointer to the D4215x structure.
 * @param speed Desired speed of the motor.
 */
void D4215_set(D4215x* bldcx, int32_t speed); // speed = [5 10]

#endif /* INC_D4215_H_ */
