/**
 * @file stepper_driver.c
 * @brief Implementation of stepper motor driver functions.
 * 
 *  Created on: May 3, 2024
 *  Author: vvinh
 */

#include "stepper_driver.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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
void stepper_init (StepperX* stepperx, TIM_HandleTypeDef* timer, uint32_t channel, GPIO_TypeDef* GPIO, uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t gearRatio) {
    stepperx->timer    = timer;
    stepperx->channel  = channel;
    stepperx->GPIOx    = GPIO;
    stepperx->EN_PIN   = EN_PIN;
    stepperx->DIR_PIN  = DIR_PIN;
    stepperx->gearRatio = gearRatio;
    stepperx->speed    = 0;
    stepperx->period   = 2000;
    HAL_TIM_PWM_Start (timer, channel);
}

/**
 * @brief Enables the stepper motor.
 * 
 * @param stepperx Pointer to the StepperX structure.
 */
void stepper_enable (StepperX* stepperx){
    HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->EN_PIN, 0);
}

/**
 * @brief Disables the stepper motor.
 * 
 * @param stepperx Pointer to the StepperX structure.
 */
void stepper_disable (StepperX* stepperx){
    HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->EN_PIN, 1);
}

/**
 * @brief Sets the speed of the stepper motor.
 * 
 * @param stepperx Pointer to the StepperX structure.
 * @param speed Desired speed of the stepper motor.
 */
void stepper_setspeed(StepperX* stepperx, int64_t speed){
    stepperx->period = speed;
    if (speed > 0){
        HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->DIR_PIN, 1);
        __HAL_TIM_SET_COMPARE(stepperx->timer, stepperx->channel, (stepperx->period)/2);
    }
    else if (speed < 0) {
        HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->DIR_PIN, 0);
        __HAL_TIM_SET_COMPARE(stepperx->timer, stepperx->channel, (stepperx->period)/2);
    }
    else {
        HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->DIR_PIN, 1);
        __HAL_TIM_SET_COMPARE(stepperx->timer, stepperx->channel, (stepperx->period)/2);
    }
    //update_speed(stepperx, abs(speed));
}

//void update_speed(StepperX* stepperx, int64_t speed){
//    stepperx->speed = speed * stepperx->gearRatio * 160/9;
//    if (stepperx->speed != 0) {
//        stepperx->period = (80000000/stepperx->speed);
//    }
//    else {
//        stepperx->period = 0;
//    }
//    (stepperx->timer)->Init.Period = stepperx->period;
//    HAL_TIM_Base_Init(stepperx->timer);
//}
