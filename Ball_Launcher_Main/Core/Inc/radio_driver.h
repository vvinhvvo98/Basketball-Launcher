/**
  ******************************************************************************
  * @file            radio_driver.h
  * @brief           Header for radio_driver.c file.
  *                  This file contains the common defines of the application.
  ******************************************************************************
  * Created on: May 2, 2024
  *
  * Author: vvinh
  */

#ifndef INC_RADIO_DRIVER_H_
#define INC_RADIO_DRIVER_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
  * @brief Structure to define a radio driver with timer, channels, and pulse width parameters.
  */
typedef struct
{
    TIM_HandleTypeDef* timer; /**< Timer handle for the radio driver */
    uint32_t channel1;        /**< Timer channel 1 */
    uint32_t channel2;        /**< Timer channel 2 */
    uint32_t sum1;            /**< Sum of pulse widths for channel 1 */
    uint32_t sum2;            /**< Sum of pulse widths for channel 2 */
    uint32_t counter1;        /**< Counter for channel 1 */
    uint32_t counter2;        /**< Counter for channel 2 */
    double pulseWidth;        /**< Pulse width */
} RadioX;

/**
  * @brief Initializes the radio driver with the specified timer and channels.
  *
  * @param radio Pointer to the RadioX structure
  * @param timer Timer handle
  * @param channel1 Timer channel 1
  * @param channel2 Timer channel 2
  */
void Radio_init(RadioX* radio, TIM_HandleTypeDef* timer, uint32_t channel1, uint32_t channel2);

/**
  * @brief Captures the pulse width for the radio driver.
  *
  * @param radio Pointer to the RadioX structure
  */
void capturePulseWidth(RadioX* radio);

/**
  * @brief Updates the radio driver with pulse width values.
  *
  * @param radio Pointer to the RadioX structure
  * @param pw1 Pulse width value for channel 1
  * @param pw2 Pulse width value for channel 2
  */
void update(RadioX* radio, int pw1, int pw2);

/**
  * @brief Gets the pulse width of the radio driver.
  *
  * @param radio Pointer to the RadioX structure
  * @return double Pulse width value
  */
double Radio_getPulseWidth(RadioX* radio);

#endif /* INC_RADIO_DRIVER_H_ */
