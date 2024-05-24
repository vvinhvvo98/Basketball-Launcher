/**
  ******************************************************************************
  * @file            stepper_driver.h
  * @brief           Header for stepper_driver.c file.
  *                  This file contains the common defines of the application.
  ******************************************************************************
  * Created on: May 17, 2024
  *
  * Author: vvinh
  */

#ifndef INC_STEPPER_DRIVER_H_
#define INC_STEPPER_DRIVER_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
/**
  * @brief Structure to define a stepper motor driver with GPIO ports and pins.
  */
typedef struct
{
	GPIO_TypeDef* GPIOx; /**< GPIO port of the stepper motor driver */
	uint16_t EN_PIN;     /**< Enable pin of the stepper motor driver */
	uint16_t DIR_PIN; 	 /**< Direction pin of the stepper motor driver */
	uint16_t STP_PIN;    /**< Step pin of the stepper motor driver */

} StepperX;

/**
  * @brief Initializes the stepper motor driver with the specified GPIO port and pins.
  *
  * @param stepperx Pointer to the StepperX structure
  * @param GPIO GPIO port
  * @param EN_PIN Enable pin
  * @param DIR_PIN Direction pin
  * @param STP_PIN Step pin
  */
void Stepper_init     (StepperX* stepperx, GPIO_TypeDef* GPIO, uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STP_PIN);

/**
  * @brief Enables the stepper motor driver.
  *
  * @param stepperx Pointer to the StepperX structure
  */
void Stepper_enable   (StepperX* stepperx);

/**
  * @brief Disables the stepper motor driver.
  *
  * @param stepperx Pointer to the StepperX structure
  */
void Stepper_disable  (StepperX* stepperx);

/**
  * @brief Sets the speed and direction of the stepper motor.
  *
  * @param stepperx Pointer to the StepperX structure
  * @param speed Speed of the stepper motor
  * @param dir Direction of the stepper motor (1 for one direction, 0 for the opposite)
  */
void Stepper_setspeed (StepperX* stepperx, uint16_t speed, uint8_t dir);


/**
  * @brief Initializes the system tick for delay functions.
  */
void SysTick_Init(void);

/**
  * @brief Delays the program execution for a specified number of microseconds.
  *
  * @param us Number of microseconds to delay
  */
void Delay_us(uint32_t us);

#endif /* INC_STEPPER_DRIVER_H_ */
