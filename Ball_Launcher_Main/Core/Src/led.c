/*
 * led.c
 *
 *  Created on: May 17, 2024
 *      Author: vvinh
 */


#include "led.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

void LED_init(LEDX* LEDx, GPIO_TypeDef* GPIO, uint16_t PIN) {
	LEDx->GPIOx    = GPIO;
	LEDx->PIN   = PIN;
}
void LED_on(LEDX* LEDx) {
	HAL_GPIO_WritePin(LEDx->GPIOx, LEDx->PIN, GPIO_PIN_SET);
}

void LED_off(LEDX* LEDx) {
	HAL_GPIO_WritePin(LEDx->GPIOx, LEDx->PIN, GPIO_PIN_RESET);
}
void LED_toggle(LEDX* LEDx){
	HAL_GPIO_TogglePin(LEDx->GPIOx, LEDx->PIN);
}
