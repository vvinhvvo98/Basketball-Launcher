/**
  ******************************************************************************
  * @file            stepper_driver.c
  * @brief           Source file for stepper motor driver operations.
  *                  This file contains the implementation of the functions for
  *                  initializing and controlling a stepper motor.
  ******************************************************************************
  * Created on: May 17, 2024
  *
  * Author: vvinh
  */

#include "stepper_driver.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

/**
  * @brief Initializes the stepper motor driver with the specified GPIO port and pins.
  *
  * @param stepperx Pointer to the StepperX structure
  * @param GPIO GPIO port
  * @param EN_PIN Enable pin
  * @param DIR_PIN Direction pin
  * @param STP_PIN Step pin
  */
void Stepper_init(StepperX* stepperx, GPIO_TypeDef* GPIO, uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STP_PIN) {
	stepperx->GPIOx    = GPIO;
	stepperx->EN_PIN   = EN_PIN;
	stepperx->DIR_PIN  = DIR_PIN;
	stepperx->STP_PIN  = STP_PIN;
}

/**
  * @brief Enables the stepper motor driver.
  *
  * @param stepperx Pointer to the StepperX structure
  */
void Stepper_enable   (StepperX* stepperx) {
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->EN_PIN, 0);
}

/**
  * @brief Disables the stepper motor driver.
  *
  * @param stepperx Pointer to the StepperX structure
  */
void Stepper_disable  (StepperX* stepperx) {
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->EN_PIN, 1);
}

/**
  * @brief Sets the speed and direction of the stepper motor.
  *
  * @param stepperx Pointer to the StepperX structure
  * @param speed Speed of the stepper motor (delay between steps)
  * @param dir Direction of the stepper motor (1 for one direction, 0 for the opposite)
  */
void Stepper_setspeed (StepperX* stepperx, uint16_t speed, uint8_t dir) {
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->DIR_PIN, dir);/**< Set the direction pin */
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->STP_PIN, 1);/**< Set the step pin high */
	Delay_us(speed);/**< Delay to control the speed */
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->STP_PIN, 0); /**< Set the step pin low */
	Delay_us(speed);/**< Delay to control the speed */

}

/**
  * @brief Initializes the system tick for microsecond delays.
  */
void SysTick_Init(void)
{
    // Assuming SystemCoreClock is already set correctly
    // Configure SysTick to trigger every 1 microsecond
    SysTick->LOAD = (SystemCoreClock / 1000000) - 1;  // Set reload register
    SysTick->VAL = 0;                                 // Reset the SysTick counter value
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick
}

/**
  * @brief Delays the program execution for a specified number of microseconds.
  *
  * @param us Number of microseconds to delay
  */
void Delay_us(uint32_t us)
{
    uint32_t startTick = SysTick->VAL;
    uint32_t ticks = us * (SystemCoreClock / 1000000);
    uint32_t elapsedTicks = 0;
    uint32_t currentTick;

    do
    {
        currentTick = SysTick->VAL;
        if (currentTick <= startTick)
        {
            elapsedTicks += startTick - currentTick;
        }
        else
        {
            elapsedTicks += startTick + (SysTick->LOAD + 1 - currentTick);
        }
        startTick = currentTick;
    } while (elapsedTicks < ticks);
}
