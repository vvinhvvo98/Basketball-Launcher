/**
  ******************************************************************************
  * @file            led.c
  * @brief           Source file for LED operations.
  *                  This file contains the implementation of the functions for
  *                  initializing and controlling an LED.
  ******************************************************************************
  * Created on: May 17, 2024
  *
  * Author: vvinh
  */

#include "led.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

/**
  * @brief Initializes the LED with the specified GPIO port and pin.
  *
  * @param LEDx Pointer to the LEDX structure
  * @param GPIO GPIO port
  * @param PIN GPIO pin
  */
void LED_init(LEDX* LEDx, GPIO_TypeDef* GPIO, uint16_t PIN) {
	LEDx->GPIOx = GPIO;/**< Assign the GPIO port */
	LEDx->PIN   = PIN;/**< Assign the GPIO pin */
}

/**
  * @brief Turns on the LED.
  *
  * @param LEDx Pointer to the LEDX structure
  */
void LED_on(LEDX* LEDx) {
	HAL_GPIO_WritePin(LEDx->GPIOx, LEDx->PIN, GPIO_PIN_SET);/**< Set the pin high to turn on the LED */
}

/**
  * @brief Turns off the LED.
  *
  * @param LEDx Pointer to the LEDX structure
  */
void LED_off(LEDX* LEDx) {
	HAL_GPIO_WritePin(LEDx->GPIOx, LEDx->PIN, GPIO_PIN_RESET); /**< Set the pin low to turn off the LED */
}

/**
  * @brief Toggles the LED state.
  *
  * @param LEDx Pointer to the LEDX structure
  */
void LED_toggle(LEDX* LEDx){
	HAL_GPIO_TogglePin(LEDx->GPIOx, LEDx->PIN); /**< Toggle the pin to change the LED state */
}
