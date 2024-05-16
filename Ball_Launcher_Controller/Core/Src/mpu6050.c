/*
 * mpu6050.c
 *
 *  Created on: May 3, 2024
 *      Author: vvinh
 */
#include "mpu6050.h"

uint16_t  mpu6050_init(MPU6050* imux, I2C_HandleTypeDef* hi2c) {
    imux->hi2c = hi2c;
    imux->gX = 0;
    imux->gY = 0;
    imux->gZ = 0;
    imux->gX_offset = 0;
    imux->gY_offset = 0;
    imux->gZ_offset = 0;
    imux->X = 0;
    imux->Y = 0;
    imux->Z = 0;
    imux->addr = 0x68;
    imux->status = HAL_I2C_IsDeviceReady(imux->hi2c, (imux->addr << 1), 1, 100);
    if (imux->status == HAL_OK) {
        	uint8_t data[2];
        	data[0] = 0x00;
            HAL_I2C_Mem_Write(imux->hi2c, (imux->addr << 1), 0x6B, I2C_MEMADD_SIZE_8BIT, data, 1, 100);
            HAL_I2C_Mem_Write(imux->hi2c, (imux->addr << 1), 0x1B, I2C_MEMADD_SIZE_8BIT, data, 1, 100);
            return 1;
	}
    else{
    	return 0;
    }
}

void mpu6050_calibrate(MPU6050* imux) {
    int16_t gX_total = 0;
    int16_t	gY_total = 0;
	int16_t gZ_total = 0;
    const int num_samples = 10;

    for (int i = 0; i < num_samples; i++) {
        mpu6050_update(imux, 10);
        gX_total += imux->gX;
        gY_total += imux->gY;
        gZ_total += imux->gZ;
        HAL_Delay(10);
    }

    imux->gX_offset = gX_total / num_samples;
    imux->gY_offset = gY_total / num_samples;
    imux->gZ_offset = gZ_total / num_samples;
    imux->X = 0;
    imux->Y = 0;
    imux->Z = 0;
}

void mpu6050_update(MPU6050* imux, uint16_t dt) {
    uint8_t data[6];
    int16_t gx, gy, gz;
    imux->status = HAL_I2C_Mem_Read(imux->hi2c, (imux->addr << 1), 0x43, I2C_MEMADD_SIZE_8BIT, data, 6, 100);

    if (imux->status == HAL_OK) {
        gx = (int16_t)((data[0] << 8) | data[1]);
        gy = (int16_t)((data[2] << 8) | data[3]);
        gz = (int16_t)((data[4] << 8) | data[5]);

        imux->gX = gx / 131;
        imux->gY = gy / 131;
        imux->gZ = gz / 131;

        imux->X += (mpu6050_get_gX(imux) * dt);
        imux->Y += (mpu6050_get_gY(imux) * dt);
        imux->Z += (mpu6050_get_gZ(imux) * dt);
    }
}


int16_t mpu6050_get_gX(MPU6050* imux){
	return (imux->gX - imux->gX_offset);
}

int16_t mpu6050_get_gY(MPU6050* imux) {
	return (imux->gY - imux->gY_offset);
}

int16_t mpu6050_get_gZ(MPU6050* imux) {
	return (imux->gZ - imux->gZ_offset);
}

int32_t mpu6050_get_X(MPU6050* imux){
	return imux->X/1000;
}

int32_t mpu6050_get_Y(MPU6050* imux) {
	return imux->Y/1000;
}
int32_t mpu6050_get_Z(MPU6050* imux) {
	return imux->Z/1000;
}
