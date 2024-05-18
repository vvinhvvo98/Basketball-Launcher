/*
 * switch.h
 *
 *  Created on: May 17, 2024
 *      Author: vvinh
 */

#ifndef INC_SWITCH_H_
#define INC_SWITCH_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct
{
	GPIO_TypeDef* GPIOx;
	uint16_t PIN;
	uint16_t status;
} SwitchX;

void Switch_init(SwitchX* switchx, GPIO_TypeDef* GPIO, uint16_t PIN);
uint8_t Switch_getStatus(SwitchX* switchx);

#endif /* INC_SWITCH_H_ */
