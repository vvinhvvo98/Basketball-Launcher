/*
 * stepper_driver.h
 *
 *  Created on: May 17, 2024
 *      Author: vvinh
 */

#ifndef INC_STEPPER_DRIVER_H_
#define INC_STEPPER_DRIVER_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct
{
	GPIO_TypeDef* GPIOx;
	uint16_t EN_PIN;
	uint16_t DIR_PIN;
	uint16_t STP_PIN;

} StepperX;

void Stepper_init     (StepperX* stepperx, GPIO_TypeDef* GPIO, uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STP_PIN);
void Stepper_enable   (StepperX* stepperx);
void Stepper_disable  (StepperX* stepperx);
void Stepper_setspeed (StepperX* stepperx, uint16_t speed, uint8_t dir);

void SysTick_Init(void);
void Delay_us(uint32_t us);
#endif /* INC_STEPPER_DRIVER_H_ */
