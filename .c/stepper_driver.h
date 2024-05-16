/**
  ******************************************************************************
  * @file            stepper_driver.h
  * @brief           Header for stepper_driver.c file.
  *                  This file contains the common defines of the application.
  ******************************************************************************
  */

#ifndef STEPPER_DRIVER_H_
#define STEPPER_DRIVER_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
 * @brief Struct representing a stepper motor.
 */
typedef struct
{
    TIM_HandleTypeDef* timer;   /**< Timer handle for PWM generation. */
    GPIO_TypeDef* GPIOx;        /**< GPIO port for control pins. */
    int64_t speed;              /**< Speed of the stepper motor. */
    uint32_t period;            /**< Period of the PWM signal. */
    uint32_t channel;           /**< Timer channel for PWM generation. */
    uint16_t EN_PIN;            /**< Enable pin for the stepper motor driver. */
    uint16_t DIR_PIN;           /**< Direction pin for the stepper motor driver. */
    uint16_t gearRatio;         /**< Gear ratio of the stepper motor. */
} StepperX;

/**
 * @brief Initializes the stepper motor.
 * 
 * @param stepperx Pointer to the StepperX structure.
 * @param timer Pointer to the timer handle.
 * @param channel Timer channel for PWM generation.
 * @param GPIO GPIO port for control pins.
 * @param EN_PIN Enable pin for the stepper motor driver.
 * @param DIR_PIN Direction pin for the stepper motor driver.
 * @param gearRatio Gear ratio of the stepper motor.
 */
void stepper_init (StepperX* stepperx, TIM_HandleTypeDef* timer, uint32_t channel, GPIO_TypeDef* GPIO, uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t gearRatio);

/**
 * @brief Enables the stepper motor.
 * 
 * @param stepperx Pointer to the StepperX structure.
 */
void stepper_enable (StepperX* stepperx);

/**
 * @brief Disables the stepper motor.
 * 
 * @param stepperx Pointer to the StepperX structure.
 */
void stepper_disable (StepperX* stepperx);

/**
 * @brief Sets the speed of the stepper motor.
 * 
 * @param stepperx Pointer to the StepperX structure.
 * @param speed Desired speed of the stepper motor.
 */
void stepper_setspeed (StepperX* stepperx, int64_t speed);

#endif /* STEPPER_DRIVER_H_ */
