################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/d4215.c \
../Core/Inc/motor_driver.c \
../Core/Inc/mpu6050.c \
../Core/Inc/radio_driver.c \
../Core/Inc/stepper_driver.c 

OBJS += \
./Core/Inc/d4215.o \
./Core/Inc/motor_driver.o \
./Core/Inc/mpu6050.o \
./Core/Inc/radio_driver.o \
./Core/Inc/stepper_driver.o 

C_DEPS += \
./Core/Inc/d4215.d \
./Core/Inc/motor_driver.d \
./Core/Inc/mpu6050.d \
./Core/Inc/radio_driver.d \
./Core/Inc/stepper_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o Core/Inc/%.su Core/Inc/%.cyclo: ../Core/Inc/%.c Core/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/d4215.cyclo ./Core/Inc/d4215.d ./Core/Inc/d4215.o ./Core/Inc/d4215.su ./Core/Inc/motor_driver.cyclo ./Core/Inc/motor_driver.d ./Core/Inc/motor_driver.o ./Core/Inc/motor_driver.su ./Core/Inc/mpu6050.cyclo ./Core/Inc/mpu6050.d ./Core/Inc/mpu6050.o ./Core/Inc/mpu6050.su ./Core/Inc/radio_driver.cyclo ./Core/Inc/radio_driver.d ./Core/Inc/radio_driver.o ./Core/Inc/radio_driver.su ./Core/Inc/stepper_driver.cyclo ./Core/Inc/stepper_driver.d ./Core/Inc/stepper_driver.o ./Core/Inc/stepper_driver.su

.PHONY: clean-Core-2f-Inc

