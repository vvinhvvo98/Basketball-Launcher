/**
  ******************************************************************************
  * @file            led.h
  * @brief           Header for led.c file.
  *                  This file contains the common defines of the application.
  ******************************************************************************
  * Created on: May 17, 2024
  *
  * Author: vvinh
  */

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
  * @brief Structure to define an LED with GPIO port and pin.
  */
typedef struct
{
	GPIO_TypeDef* GPIOx; /**< GPIO port of the LED */
	uint16_t PIN; 		 /**< GPIO pin of the LED */
} LEDX;

/**
  * @brief Initializes the LED with the specified GPIO port and pin.
  *
  * @param LEDx Pointer to the LEDX structure
  * @param GPIO GPIO port
  * @param PIN GPIO pin
  */
void LED_init(LEDX* LEDx, GPIO_TypeDef* GPIO, uint16_t PIN);

/**
  * @brief Turns on the LED.
  *
  * @param LEDx Pointer to the LEDX structure
  */
void LED_on(LEDX* LEDx);

/**
  * @brief Turns off the LED.
  *
  * @param LEDx Pointer to the LEDX structure
  */
void LED_off(LEDX* LEDx);

/**
  * @brief Toggles the LED state.
  *
  * @param LEDx Pointer to the LEDX structure
  */
void LED_toggle(LEDX* LEDx);

#endif /* INC_LED_H_ */
