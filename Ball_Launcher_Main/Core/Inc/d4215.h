/**
  ******************************************************************************
  * @file            d4215.h
  * @brief           Header for d4215.c file.
  *                  This file contains the common defines of the application.
  ******************************************************************************
  * Created on: May 1, 2024
  *
  * Author: vvinh
  */

#ifndef INC_D4215_H_
#define INC_D4215_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
  * @brief Structure to define a D4215 motor with timer, channel, and speed.
  */
typedef struct
{
	TIM_HandleTypeDef* timer; 	/**< Timer handle for the motor */
    uint32_t channel;			/**< Timer channel for the motor */
    int32_t speed;				/**< Speed of the motor */
} D4215X;

/**
  * @brief Initializes the D4215 motor with the specified timer and channel.
  *
  * @param bldcx Pointer to the D4215X structure
  * @param timer Timer handle
  * @param channel Timer channel
  */
void D4215_init(D4215X* bldcx, TIM_HandleTypeDef* timer, uint32_t channel);

/**
  * @brief Sets the speed of the D4215 motor.
  *
  * @param bldcx Pointer to the D4215X structure
  * @param speed Speed of the motor (range: 0 to 100)
  */
void D4215_set (D4215X* bldcx, int32_t speed);


#endif /* INC_D4215_H_ */
