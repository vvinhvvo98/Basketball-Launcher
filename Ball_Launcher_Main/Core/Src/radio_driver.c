/**
  ******************************************************************************
  * @file            radio_driver.c
  * @brief           Source file for radio driver operations.
  *                  This file contains the implementation of the functions for
  *                  initializing and handling a radio driver.
  ******************************************************************************
  * Created on: May 2, 2024
  *
  * Author: vvinh
  */

#include "radio_driver.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

/**
  * @brief Initializes the radio driver with the specified timer and channels.
  *
  * @param radio Pointer to the RadioX structure
  * @param timer Timer handle
  * @param channel1 Timer channel 1
  * @param channel2 Timer channel 2
  */
void Radio_init(RadioX* radio, TIM_HandleTypeDef* timer, uint32_t channel1, uint32_t channel2) {

    radio->timer = timer;
    radio->channel1 = channel1;
    radio->channel2 = channel2;

    HAL_TIM_IC_Start_IT(timer, channel1); /**< Start input capture interrupt for channel 1 */
    HAL_TIM_IC_Start_IT(timer, channel2); /**< Start input capture interrupt for channel 2 */

    radio->sum1 = 0;
    radio->sum2 = 0;
    radio->counter1 = 0;
    radio->counter2 = 0;
    radio->pulseWidth = 0;
}

/**
  * @brief Captures the pulse width for the radio driver.
  *
  * @param radio Pointer to the RadioX structure
  */
void capturePulseWidth(RadioX* radio) {
    int pw1 = HAL_TIM_ReadCapturedValue(radio->timer, radio->channel1); /**< Read captured value for channel 1 */
    int pw2 = HAL_TIM_ReadCapturedValue(radio->timer, radio->channel2); /**< Read captured value for channel 2 */
    update(radio, pw1, pw2);
    radio->pulseWidth = (double)(radio->counter2 - radio->counter1); /**< Calculate the pulse width */
}

/**
  * @brief Updates the radio driver with pulse width values.
  *
  * @param radio Pointer to the RadioX structure
  * @param pw1 Pulse width value for channel 1
  * @param pw2 Pulse width value for channel 2
  */
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

/**
  * @brief Gets the pulse width of the radio driver.
  *
  * @param radio Pointer to the RadioX structure
  * @return double Pulse width value in milliseconds
  */
double Radio_getPulseWidth(RadioX* radio) {
    if (radio->pulseWidth > 2000.00) {
        return 0;
    } else {
        return radio->pulseWidth / 1000.00;
    }
}
