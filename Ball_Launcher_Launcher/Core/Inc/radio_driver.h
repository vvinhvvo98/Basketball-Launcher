/**
  ******************************************************************************
  * @file            radio_driver.h
  * @brief           Header for radio_driver.c file.
  *                  This file contains the common defines of the application.
  ******************************************************************************
  */

#ifndef INC_RADIO_DRIVER_H_
#define INC_RADIO_DRIVER_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
 * @brief Struct representing a radio driver.
 */
typedef struct
{
    TIM_HandleTypeDef* timer;   /**< Timer handle for PWM measurement. */
    uint32_t channel1;          /**< Timer channel 1 for PWM measurement. */
    uint32_t channel2;          /**< Timer channel 2 for PWM measurement. */
    uint32_t sum1;              /**< Sum of captured values for channel 1. */
    uint32_t sum2;              /**< Sum of captured values for channel 2. */
    uint32_t counter1;          /**< Counter for number of captures on channel 1. */
    uint32_t counter2;          /**< Counter for number of captures on channel 2. */
    double pulseWidth;          /**< Calculated pulse width. */

} RadioX;

/**
 * @brief Initializes the radio driver.
 * 
 * @param radio Pointer to the RadioX structure.
 * @param timer Pointer to the timer handle.
 * @param channel1 Timer channel 1 for PWM measurement.
 * @param channel2 Timer channel 2 for PWM measurement.
 */
void Radio_init(RadioX* radio, TIM_HandleTypeDef* timer, uint32_t channel1, uint32_t channel2);

/**
 * @brief Captures the pulse width from the radio signal.
 * 
 * @param radio Pointer to the RadioX structure.
 */
void capturePulseWidth(RadioX* radio);

/**
 * @brief Updates the pulse width values.
 * 
 * @param radio Pointer to the RadioX structure.
 * @param pw1 Pulse width value for channel 1.
 * @param pw2 Pulse width value for channel 2.
 */
void update(RadioX* radio, int pw1, int pw2);

/**
 * @brief Gets the calculated pulse width.
 * 
 * @param radio Pointer to the RadioX structure.
 * @return Calculated pulse width.
 */
double Radio_getPulseWidth(RadioX* radio);

#endif /* INC_RADIO_DRIVER_H_ */
