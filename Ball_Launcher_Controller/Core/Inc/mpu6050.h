/*
 * mpu6050.h
 *
 *  Created on: May 3, 2024
 *      Author: vvinh
 */
#ifndef MPU6050_H_
#define MPU6050_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct
{
	I2C_HandleTypeDef* hi2c;
	HAL_StatusTypeDef status;
    uint16_t addr;
    uint16_t dt;

    int16_t gX;
    int16_t gY;
    int16_t gZ;

    int16_t gX_offset;
    int16_t gY_offset;
    int16_t gZ_offset;

    int32_t X;
    int32_t Y;
    int32_t Z;


} MPU6050;

uint16_t  mpu6050_init(MPU6050* imux, I2C_HandleTypeDef* hi2c);
void mpu6050_calibrate(MPU6050* imu);
void mpu6050_update(MPU6050* imux, uint16_t dt);

int16_t mpu6050_get_gX(MPU6050* imux);
int16_t mpu6050_get_gY(MPU6050* imux);
int16_t mpu6050_get_gZ(MPU6050* imux);

int32_t mpu6050_get_X(MPU6050* imux);
int32_t mpu6050_get_Y(MPU6050* imux);
int32_t mpu6050_get_Z(MPU6050* imux);
#endif /* MPU6050_H_ */
