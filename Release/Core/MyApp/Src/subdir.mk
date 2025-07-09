################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MyApp/Src/output.c \
../Core/MyApp/Src/studentstuff.c \
../Core/MyApp/Src/taskcreate.c 

OBJS += \
./Core/MyApp/Src/output.o \
./Core/MyApp/Src/studentstuff.o \
./Core/MyApp/Src/taskcreate.o 

C_DEPS += \
./Core/MyApp/Src/output.d \
./Core/MyApp/Src/studentstuff.d \
./Core/MyApp/Src/taskcreate.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MyApp/Src/%.o: ../Core/MyApp/Src/%.c Core/MyApp/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-MyApp-2f-Src

clean-Core-2f-MyApp-2f-Src:
	-$(RM) ./Core/MyApp/Src/output.d ./Core/MyApp/Src/output.o ./Core/MyApp/Src/studentstuff.d ./Core/MyApp/Src/studentstuff.o ./Core/MyApp/Src/taskcreate.d ./Core/MyApp/Src/taskcreate.o

.PHONY: clean-Core-2f-MyApp-2f-Src

