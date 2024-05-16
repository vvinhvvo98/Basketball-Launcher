/*
 * stepper_driver.h
 *
 *  Created on: May 9, 2024
 *      Author: vvinh
 */

#ifndef STEPPER_DRIVER_H_
#define STEPPER_DRIVER_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct
{
	TIM_HandleTypeDef* timer;
	GPIO_TypeDef* GPIOx;
    int64_t speed;
	uint32_t period;
    uint32_t channel;
	uint16_t EN_PIN;
	uint16_t DIR_PIN;
	uint16_t gearRatio;

} StepperX;

// Prototype for motor object "method"
void stepper_init     (StepperX* stepperx, TIM_HandleTypeDef* timer, uint32_t channel, GPIO_TypeDef* GPIO, uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t gearRatio);
void stepper_enable   (StepperX* stepperx);
void stepper_disable  (StepperX* stepperx);
void stepper_setspeed (StepperX* stepperx, int64_t speed);
//void update_speed     (StepperX* stepperx, int64_t speed);
#endif /* STEPPER_DRIVER_H_ */
