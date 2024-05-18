/*
 * stepper_driver.c
 *
 *  Created on: May 17, 2024
 *      Author: vvinh
 */
#include "stepper_driver.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

void Stepper_init(StepperX* stepperx, GPIO_TypeDef* GPIO, uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STP_PIN) {
	stepperx->GPIOx    = GPIO;
	stepperx->EN_PIN   = EN_PIN;
	stepperx->DIR_PIN  = DIR_PIN;
	stepperx->STP_PIN  = STP_PIN;
}

void Stepper_enable   (StepperX* stepperx) {
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->EN_PIN, 0);
}
void Stepper_disable  (StepperX* stepperx) {
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->EN_PIN, 1);
}
void Stepper_setspeed (StepperX* stepperx, uint16_t speed, uint8_t dir) {
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->DIR_PIN, dir);
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->STP_PIN, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->STP_PIN, 0);
	HAL_Delay(speed);

}
