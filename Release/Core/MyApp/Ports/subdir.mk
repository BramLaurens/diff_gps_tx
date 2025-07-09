################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MyApp/Ports/buzzer.c \
../Core/MyApp/Ports/keys.c \
../Core/MyApp/Ports/lcd.c \
../Core/MyApp/Ports/leds.c \
../Core/MyApp/Ports/uart.c 

OBJS += \
./Core/MyApp/Ports/buzzer.o \
./Core/MyApp/Ports/keys.o \
./Core/MyApp/Ports/lcd.o \
./Core/MyApp/Ports/leds.o \
./Core/MyApp/Ports/uart.o 

C_DEPS += \
./Core/MyApp/Ports/buzzer.d \
./Core/MyApp/Ports/keys.d \
./Core/MyApp/Ports/lcd.d \
./Core/MyApp/Ports/leds.d \
./Core/MyApp/Ports/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MyApp/Ports/%.o: ../Core/MyApp/Ports/%.c Core/MyApp/Ports/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-MyApp-2f-Ports

clean-Core-2f-MyApp-2f-Ports:
	-$(RM) ./Core/MyApp/Ports/buzzer.d ./Core/MyApp/Ports/buzzer.o ./Core/MyApp/Ports/keys.d ./Core/MyApp/Ports/keys.o ./Core/MyApp/Ports/lcd.d ./Core/MyApp/Ports/lcd.o ./Core/MyApp/Ports/leds.d ./Core/MyApp/Ports/leds.o ./Core/MyApp/Ports/uart.d ./Core/MyApp/Ports/uart.o

.PHONY: clean-Core-2f-MyApp-2f-Ports

