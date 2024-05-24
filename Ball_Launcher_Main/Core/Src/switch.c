/**
  ******************************************************************************
  * @file            switch.c
  * @brief           Source file for switch operations.
  *                  This file contains the implementation of the functions for
  *                  initializing and getting the status of a switch.
  ******************************************************************************
  * Created on: May 17, 2024
  *
  * Author: vvinh
  */

#include "switch.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>


/**
  * @brief Initializes the switch with the specified GPIO port and pin.
  *
  * @param switchx Pointer to the SwitchX structure
  * @param GPIO GPIO port
  * @param PIN GPIO pin
  */
void Switch_init(SwitchX* switchx, GPIO_TypeDef* GPIO, uint16_t PIN) {
    switchx->GPIOx = GPIO;     /**< Assign the GPIO port */
    switchx->PIN   = PIN;      /**< Assign the GPIO pin */
    switchx->status= 0;        /**< Initialize the status to 0 */
}

/**
  * @brief Gets the status of the switch.
  *
  * @param switchx Pointer to the SwitchX structure
  * @return uint8_t Status of the switch (1 if pressed, 0 if not pressed)
  */
uint8_t Switch_getStatus(SwitchX* switchx) {
	switchx->status = HAL_GPIO_ReadPin(switchx->GPIOx, switchx->PIN);
	return switchx->status;
}

