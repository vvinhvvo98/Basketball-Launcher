/*
 * stepper_driver.c
 *
 *  Created on: May 17, 2024
 *      Author: vvinh
 */
#include "stepper_driver.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>

void Stepper_init(StepperX* stepperx, GPIO_TypeDef* GPIO, uint16_t EN_PIN, uint16_t DIR_PIN, uint16_t STP_PIN) {
	stepperx->GPIOx    = GPIO;
	stepperx->EN_PIN   = EN_PIN;
	stepperx->DIR_PIN  = DIR_PIN;
	stepperx->STP_PIN  = STP_PIN;
}

void Stepper_enable   (StepperX* stepperx) {
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->EN_PIN, 0);
}
void Stepper_disable  (StepperX* stepperx) {
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->EN_PIN, 1);
}
void Stepper_setspeed (StepperX* stepperx, uint16_t speed, uint8_t dir) {
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->DIR_PIN, dir);
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->STP_PIN, 1);
	Delay_us(speed);
	HAL_GPIO_WritePin (stepperx->GPIOx, stepperx->STP_PIN, 0);
	Delay_us(speed);

}

// SysTick Initialization for microsecond delays
void SysTick_Init(void)
{
    // Assuming SystemCoreClock is already set correctly
    // Configure SysTick to trigger every 1 microsecond
    SysTick->LOAD = (SystemCoreClock / 1000000) - 1;  // Set reload register
    SysTick->VAL = 0;                                 // Reset the SysTick counter value
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick
}

// Microsecond delay function
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
