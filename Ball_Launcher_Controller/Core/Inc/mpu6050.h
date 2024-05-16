/**
  ******************************************************************************
  * @file           : mpu6050.h
  * @brief          : Header for mpu.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  */

#ifndef MPU6050_H_
#define MPU6050_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
 * @brief MPU6050 structure definition.
 */
typedef struct
{
    I2C_HandleTypeDef* hi2c; /**< I2C handle */
    HAL_StatusTypeDef status; /**< HAL status */
    uint16_t addr; /**< I2C address */
    uint16_t dt; /**< Delta time */

    int16_t gX; /**< Gyroscope X axis data */
    int16_t gY; /**< Gyroscope Y axis data */
    int16_t gZ; /**< Gyroscope Z axis data */

    int16_t gX_offset; /**< Gyroscope X axis offset */
    int16_t gY_offset; /**< Gyroscope Y axis offset */
    int16_t gZ_offset; /**< Gyroscope Z axis offset */

    int32_t X; /**< Accelerometer X axis data */
    int32_t Y; /**< Accelerometer Y axis data */
    int32_t Z; /**< Accelerometer Z axis data */

} MPU6050;

/**
 * @brief Initializes the MPU6050 sensor.
 * 
 * @param imux Pointer to the MPU6050 structure.
 * @param hi2c Pointer to the I2C handle structure.
 * @return uint16_t Returns 1 if initialization is successful, otherwise 0.
 */
uint16_t mpu6050_init(MPU6050* imux, I2C_HandleTypeDef* hi2c);

/**
 * @brief Calibrates the MPU6050 sensor.
 * 
 * @param imux Pointer to the MPU6050 structure.
 */
void mpu6050_calibrate(MPU6050* imux);

/**
 * @brief Updates the MPU6050 sensor data.
 * 
 * @param imux Pointer to the MPU6050 structure.
 * @param dt Time interval in milliseconds.
 */
void mpu6050_update(MPU6050* imux, uint16_t dt);

/**
 * @brief Gets the calibrated X-axis gyroscope data.
 * 
 * @param imux Pointer to the MPU6050 structure.
 * @return int16_t Calibrated X-axis gyroscope data.
 */
int16_t mpu6050_get_gX(MPU6050* imux);

/**
 * @brief Gets the calibrated Y-axis gyroscope data.
 * 
 * @param imux Pointer to the MPU6050 structure.
 * @return int16_t Calibrated Y-axis gyroscope data.
 */
int16_t mpu6050_get_gY(MPU6050* imux);

/**
 * @brief Gets the calibrated Z-axis gyroscope data.
 * 
 * @param imux Pointer to the MPU6050 structure.
 * @return int16_t Calibrated Z-axis gyroscope data.
 */
int16_t mpu6050_get_gZ(MPU6050* imux);

/**
 * @brief Gets the X-axis accelerometer data.
 * 
 * @param imux Pointer to the MPU6050 structure.
 * @return int32_t X-axis accelerometer data.
 */
int32_t mpu6050_get_X(MPU6050* imux);

/**
 * @brief Gets the Y-axis accelerometer data.
 * 
 * @param imux Pointer to the MPU6050 structure.
 * @return int32_t Y-axis accelerometer data.
 */
int32_t mpu6050_get_Y(MPU6050* imux);

/**
 * @brief Gets the Z-axis accelerometer data.
 * 
 * @param imux Pointer to the MPU6050 structure.
 * @return int32_t Z-axis accelerometer data.
 */
int32_t mpu6050_get_Z(MPU6050* imux);

#endif /* MPU6050_H_ */
