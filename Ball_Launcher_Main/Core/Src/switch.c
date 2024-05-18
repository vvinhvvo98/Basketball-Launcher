/*
 * switch.c
 *
 *  Created on: May 17, 2024
 *      Author: vvinh
 */

/*
 * stepper_driver.c
 *
 *  Created on: May 9, 2024
 *      Author: vvinh
 */

#include "switch.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

void Switch_init(SwitchX* switchx, GPIO_TypeDef* GPIO, uint16_t PIN) {
    switchx->GPIOx = GPIO;
	switchx->PIN   = PIN;
	switchx->status= 0;
}

uint8_t Switch_getStatus(SwitchX* switchx) {
	switchx->status = HAL_GPIO_ReadPin(switchx->GPIOx, switchx->PIN);
	return switchx->status;
}

