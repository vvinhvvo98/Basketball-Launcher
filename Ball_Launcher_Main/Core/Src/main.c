/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           main.c
  * @brief          Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "stepper_driver.h"
#include "switch.h"
#include "d4215.h"
#include "led.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
// Initiate data buffer
char charIn;
char data[20];

// Initiate reset timer parameter
uint32_t ti = 0;
uint32_t tf = 0;
uint32_t dt = 0;

// Initiate yaw + pitch angle + target angle for steppers
uint16_t yaw = 0;
uint16_t pitch = 0;
uint16_t angleTarget = 0;

// Initiate rise fall and total for radio driver
uint16_t rise = 0;
uint16_t fall = 0;
uint16_t total = 0;

// Initiate yaw and pitch direction from controller and direction from the switch
uint8_t yawDirection   = 0;
uint8_t pitchDirection = 0;
uint8_t yawDirectionSW   = 0;
uint8_t pitchDirectionSW = 0;

// Initiate flags
uint8_t idx   = 0;
uint8_t MOVE  = 0;
uint8_t SHOT  = 0;
uint8_t ESTOP = 0;
uint8_t CAL   = 0;
uint8_t HOME  = 0;
uint8_t SW1   = 0;
uint8_t SW2   = 0;
uint8_t SW3   = 0;
uint8_t SW    = 0;

// Initiate STATE & STATE NUMBER
uint8_t STATE 		    = 0;
uint8_t STATE_0_INIT    = 0;
uint8_t STATE_1_HUB     = 1;
uint8_t STATE_2_ESTOP   = 2;
uint8_t STATE_3_STEPPER = 3;
uint8_t STATE_4_BLDC    = 4;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void dataProcess(char* data);
uint16_t speedCalculate(uint16_t first, uint16_t second, uint16_t third);
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  // Create desired object
  StepperX STEPPER1;
  StepperX STEPPER2;
  D4215X ESC1;
  D4215X ESC2;
  SwitchX S1;
  SwitchX S2;
  SwitchX S3;
  LEDX LED1;
  LEDX LED2;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Print to UART6 for debug
      char buffer[100];
	  HAL_UART_Receive_IT(&huart1, (uint8_t *)&charIn, 1);
      snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%d\t\r\n", MOVE, SHOT, ESTOP, STATE);
      HAL_UART_Transmit(&huart6, (uint8_t *)buffer, strlen(buffer), 100);

      // Run Finite State Machine

      // STATE 0: INIT ALL OBJECTS
	  if (STATE == STATE_0_INIT) {
		  // INIT RADIO TIMER
		  HAL_TIM_Base_Start(&htim4);
		  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
		  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);
		  // INIT STEPPER MOTOR
  		  Stepper_init(&STEPPER1, GPIOA, GPIO_PIN_3, GPIO_PIN_5, GPIO_PIN_7);
  		  Stepper_init(&STEPPER2, GPIOA, GPIO_PIN_4, GPIO_PIN_6, GPIO_PIN_8);
  		  // INIT D4215 BLDC MOTORS
  		  D4215_init  (&ESC1,&htim2,TIM_CHANNEL_2);
  		  D4215_init  (&ESC2,&htim2,TIM_CHANNEL_3);
  		  // INIT 3 LIMIT SWITCHES
  		  Switch_init (&S1, GPIOB, GPIO_PIN_0);
  		  Switch_init (&S2, GPIOB, GPIO_PIN_1);
  		  Switch_init (&S3, GPIOB, GPIO_PIN_2);
  		  // INIT 2 EXTRA LEDS
  		  LED_init    (&LED1, GPIOB, GPIO_PIN_14);
  		  LED_init    (&LED2, GPIOB, GPIO_PIN_15);
  		  // MOVE --> STATE 1: DECISION HUB
  		  STATE = STATE_1_HUB;
	  }

	  // STATE 1: DECISION HUB TO BRANCH TO DIFFERENT HUB
	  else if (STATE == STATE_1_HUB) {
		  LED_off(&LED1);
		  LED_off(&LED2);
		  // ENABLE 2 STEPPERS
  		  Stepper_enable(&STEPPER1);
  		  Stepper_enable(&STEPPER2);
  		  // READ 3 LIMIT SWITCHES
		  SW1   = Switch_getStatus(&S1);
		  SW2   = Switch_getStatus(&S2);
		  SW3   = Switch_getStatus(&S3);
		  // CHECK ESTOP
		  if (ESTOP == 1) {
			  ti = HAL_GetTick();
			  STATE = STATE_2_ESTOP;
		  }
		  // CHECK LIMIT SWITCHES OR "MOVE" FLAG FROM CONTROLLER
		  else if ((MOVE == 1 && SHOT == 0) || SW1 == 0 || SW2 == 0 || SW3 == 0) {
			  if (SW1 == 0) {
			      SW = 1;
			      angleTarget = 10;
			      yawDirectionSW = 0;
			  } else if (SW2 == 0) {
			      SW = 2;
			      angleTarget = 10;
			      yawDirectionSW = 1;
			  } else if (SW3 == 0) {
				  SW = 3;
			      angleTarget = 10;
			      pitchDirectionSW = 0;
			  } else {
				  angleTarget = 10;
				  SW = 0;
			  }
			  STATE = STATE_3_STEPPER;
		  }
		  // CHECK "SHOT" FLAG FROM CONTROLLER
		  else if (MOVE == 0 && SHOT == 1) {
			  STATE = STATE_4_BLDC;
		  }
		  // STOP IF
		  else {
			  D4215_set(&ESC1, 0);
			  D4215_set(&ESC2, 0);
			  STATE = STATE_1_HUB;
		  }
	  }
	  // STATE 2: EMERGENCY STOP STATE
	  else if (STATE == STATE_2_ESTOP) {
		  // DISABLE STEPPER MOTORS
  		  Stepper_disable(&STEPPER1);
  		  Stepper_disable(&STEPPER2);
  		  // STOP BLDC MOTORS
		  D4215_set(&ESC1, 0);
		  D4215_set(&ESC2, 0);
		  // CHECK FOR RESET BY PUSHING 2 BUTTONS AT THE SAME TIME FOR 5 SECONDS
		  if (MOVE == 1 && SHOT == 1) {
			  tf = HAL_GetTick();
			  dt += (tf-ti);
			  ti = tf;
		  }
		  else {
			  dt = 0;
		  }
		  STATE = (dt > 5000) ? STATE_1_HUB : STATE_2_ESTOP;

	  }
	  // STATE 3: SPIN STEPPER MOTORS
	  else if (STATE == STATE_3_STEPPER) {\
		  LED_on(&LED1);
		  // LEFT SWITCH HIT --> MOVE TO THE RIGHT
		  if (SW == 1) {
			  for (int i = 0; i <= angleTarget/2; i++) {
				  Stepper_setspeed (&STEPPER1, 10, yawDirectionSW);
			  }
			  SW = 0;
		  }
		  // RIGHT SWITCH HIT --> MOVE TO THE LEFT
		  else if (SW == 2) {
			  for (int i = 0; i <= angleTarget/2; i ++) {
				  Stepper_setspeed (&STEPPER1, 10, yawDirectionSW);
			  }
			  SW = 0;
		  }
		  // MID SWITCH HIT --> MOVE UP
		  else if (SW == 3) {
			  for (int i = 0; i <= 10 * angleTarget/2; i ++) {
				  Stepper_setspeed (&STEPPER2, 10, pitchDirectionSW);
			  }
			  SW = 0;
		  }
		  // IF NOT SWITCH, MOVE ACCODING TO THE IMU DATA
		  else {
			  uint16_t yaw_map = map(yaw, 20, 250, 5, 30);
			  if (yaw > 20) {
				  for (int i = 0; i <= yaw_map; i ++) {
					  Stepper_setspeed (&STEPPER1, 1, yawDirection);
				  }
			  }
			  uint16_t pitch_map = map(pitch, 20, 250, 5, 50);
			  if (pitch > 20) {
				  for (int i = 0; i <= pitch_map; i ++) {
					  Stepper_setspeed (&STEPPER2, 1, pitchDirection);
				  }
			  }
		  }
		  STATE = STATE_1_HUB;
	  }

	  // STATE 4: BLDC MOTOR
	  else if (STATE == STATE_4_BLDC) {
		  LED_on(&LED2);
		  D4215_set(&ESC1, 30);
		  D4215_set(&ESC2, 30);
		  STATE = STATE_1_HUB;
	  }

	  // STATE 1: DECISION HUB IN CASE SOME ERROR
	  else {
		  STATE = STATE_1_HUB;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 95;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 19999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 95;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 17499;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6
                           PA7 PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB12 PB13 PB14
                           PB15 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    if (charIn == '\n')
    {
      data[idx] = '\0'; // Null-terminate the buffer
//      HAL_UART_Transmit(&huart6, (uint8_t*)data, idx, 100);
//      HAL_UART_Transmit(&huart6, (uint8_t*)"\r\n", 2, 100);
      dataProcess(data);
      idx = 0;
    }
    else
    {
      if (idx < sizeof(data) - 1)
      {
        data[idx++] = charIn;
      }
    }
    // Restart UART receive interrupt for next character
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&charIn, 1);
  }
}

void dataProcess(char* data) {
	MOVE = (int16_t)data[0] - 48;
	SHOT = (int16_t)data[2] - 48;
	yawDirection   = ((uint8_t)data[4] == 45) ? 0 : 1;
	pitchDirection = ((uint8_t)data[9] == 45) ? 0 : 1;
//	if (pitchDirection == 0) {
//		pitchDirection == 1;
//	} else {
//		pitchDirection == 0;
//	}
//
//	if (yawDirection == 0) {
//		yawDirection == 1;
//	} else {
//		yawDirection == 0;
//	}

	uint16_t yaw1 = (uint16_t)data[5] - 48;
	uint16_t yaw2 = (uint16_t)data[6] - 48;
	uint16_t yaw3 = (uint16_t)data[7] - 48;

	uint16_t pitch1 = (uint16_t)data[10] - 48;
	uint16_t pitch2 = (uint16_t)data[11] - 48;
	uint16_t pitch3 = (uint16_t)data[12] - 48;

	yaw   = speedCalculate(yaw1, yaw2, yaw3);
	pitch = speedCalculate(pitch1, pitch2, pitch3);
}


uint16_t speedCalculate(uint16_t first, uint16_t second, uint16_t third) {
	uint16_t number = 100 * first + 10 * second + 1 * third;
	return number;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM4) {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
            rise = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
        } else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
            fall = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
            if (fall >= rise) {
                total = fall - rise;
            } else {
                total = UINT16_MAX - rise + fall + 1;
            }

            if (total > 1800 && total < 2200) {
            	ESTOP = 1;
            }
            else {
            	ESTOP = 0;
            }
        }
    }
}
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (uint16_t)((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
