/*
 * radio_diver.c
 *
 *  Created on: May 2, 2024
 *      Author: vvinh
 */

#include "radio_driver.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

void Radio_init(RadioX* radio, TIM_HandleTypeDef* timer, uint32_t channel1, uint32_t channel2) {

	radio->timer = timer;

    radio->channel1 = channel1;
    radio->channel2 = channel2;

    HAL_TIM_IC_Start_IT(timer, channel1);
    HAL_TIM_IC_Start_IT(timer, channel2);

    radio->sum1 = 0;
    radio->sum2 = 0;

    radio->counter1 = 0;
    radio->counter2 = 0;

    radio->pulseWidth = 0;
}

void capturePulseWidth(RadioX* radio) {
	    int pw1 = HAL_TIM_ReadCapturedValue(radio->timer, radio->channel1);
	    int pw2 = HAL_TIM_ReadCapturedValue(radio->timer, radio->channel2);
	    update(radio, pw1, pw2);
	    radio->pulseWidth = (double)(radio->counter2 - radio->counter1);
}

void update(RadioX* radio, int pw1, int pw2) {
    const int max = 19000;
    int delta1, delta2;
    if (pw1 < radio->sum1) {
        delta1 = (max - radio->sum1 - 1) + pw1;
    } else {
        delta1 = pw1 - radio->sum1;
    }
    if (pw2 < radio->sum2) {
        delta2 = (max - radio->sum2 - 1) + pw2;
    } else {
        delta2 = pw2 - radio->sum2;
    }
    radio->sum1 = pw1;
    radio->sum2 = pw2;
    radio->counter1 += delta1;
    radio->counter2 += delta2;
}

double Radio_getPulseWidth(RadioX* radio) {
    if (radio->pulseWidth > 2000.00) {
        return 0;
    } else {
        return radio->pulseWidth / 1000.00;
    }
}




