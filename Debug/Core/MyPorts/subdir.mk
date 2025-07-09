################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MyPorts/buzzer.c \
../Core/MyPorts/keys.c \
../Core/MyPorts/lcd.c \
../Core/MyPorts/leds.c \
../Core/MyPorts/uart.c 

OBJS += \
./Core/MyPorts/buzzer.o \
./Core/MyPorts/keys.o \
./Core/MyPorts/lcd.o \
./Core/MyPorts/leds.o \
./Core/MyPorts/uart.o 

C_DEPS += \
./Core/MyPorts/buzzer.d \
./Core/MyPorts/keys.d \
./Core/MyPorts/lcd.d \
./Core/MyPorts/leds.d \
./Core/MyPorts/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MyPorts/%.o: ../Core/MyPorts/%.c Core/MyPorts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-MyPorts

clean-Core-2f-MyPorts:
	-$(RM) ./Core/MyPorts/buzzer.d ./Core/MyPorts/buzzer.o ./Core/MyPorts/keys.d ./Core/MyPorts/keys.o ./Core/MyPorts/lcd.d ./Core/MyPorts/lcd.o ./Core/MyPorts/leds.d ./Core/MyPorts/leds.o ./Core/MyPorts/uart.d ./Core/MyPorts/uart.o

.PHONY: clean-Core-2f-MyPorts

