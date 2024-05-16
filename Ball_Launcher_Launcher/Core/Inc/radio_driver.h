/*
 * radio_driver.h
 *
 *  Created on: May 2, 2024
 *      Author: vvinh
 */

#ifndef INC_RADIO_DRIVER_H_
#define INC_RADIO_DRIVER_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct
{
	TIM_HandleTypeDef* timer;
    uint32_t channel1;
    uint32_t channel2;
    uint32_t sum1;
    uint32_t sum2;
    uint32_t counter1;
    uint32_t counter2;
    double pulseWidth;

} RadioX;

void Radio_init(RadioX* radio, TIM_HandleTypeDef* timer, uint32_t channel1, uint32_t channel2);
void capturePulseWidth(RadioX* radio);
void update(RadioX* radio, int pw1, int pw2);
double Radio_getPulseWidth(RadioX* radio);

#endif /* INC_RADIO_DRIVER_H_ */
