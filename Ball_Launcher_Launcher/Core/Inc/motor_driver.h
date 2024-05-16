/*
 * motor_driver.h
 *
 *  Created on: Apr 18, 2024
 *      Author: vvinh
 */

#ifndef INC_MOTOR_DRIVER_H_
#define INC_MOTOR_DRIVER_H_
#include <stdio.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"

typedef struct
{
	TIM_HandleTypeDef* timer;
    uint32_t channel1;
    uint32_t channel2;
    int32_t duty;
    int32_t CCR;
} MotorX;

// Prototype for motor object "method"
void motor_init   (MotorX* motx, TIM_HandleTypeDef* timer, uint32_t channel1, uint32_t channel2, int32_t CCR);
void motor_enable (MotorX* motx);
void motor_setduty(MotorX* motx, int32_t duty);
void motor_disable(MotorX* motx);

#endif /* INC_MOTOR_DRIVER_H_ */
