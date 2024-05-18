/*
 * led.h
 *
 *  Created on: May 17, 2024
 *      Author: vvinh
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct
{
	GPIO_TypeDef* GPIOx;
	uint16_t PIN;
} LEDX;

void LED_init(LEDX* LEDx, GPIO_TypeDef* GPIO, uint16_t PIN);
void LED_on(LEDX* LEDx);
void LED_off(LEDX* LEDx);
void LED_toggle(LEDX* LEDx);

#endif /* INC_LED_H_ */
