/**
  ******************************************************************************
  * @file            switch.h
  * @brief           Header for switch.c file.
  *                  This file contains the common defines of the application.
  ******************************************************************************
  * Created on: May 17, 2024
  *
  * Author: vvinh
  */

#ifndef INC_SWITCH_H_
#define INC_SWITCH_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
 * @brief Structure to define a switch with GPIO port, pin, and status.
 */

typedef struct
{
    GPIO_TypeDef* GPIOx; /**< GPIO port of the switch */
    uint16_t PIN;        /**< GPIO pin of the switch */
    uint16_t status;     /**< Status of the switch */
} SwitchX;

/**
 * @brief Initializes the switch with the specified GPIO port and pin.
 *
 * @param switchx Pointer to the SwitchX structure
 * @param GPIO GPIO port
 * @param PIN GPIO pin
 */
void Switch_init(SwitchX* switchx, GPIO_TypeDef* GPIO, uint16_t PIN);

/**
 * @brief Gets the status of the switch.
 *
 * @param switchx Pointer to the SwitchX structure
 * @return uint8_t Status of the switch (1 if pressed, 0 if not pressed)
 */
uint8_t Switch_getStatus(SwitchX* switchx);

#endif /* INC_SWITCH_H_ */
