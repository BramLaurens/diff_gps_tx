################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MyApp/App/mutex.c \
../Core/MyApp/App/my_app.c \
../Core/MyApp/App/output.c \
../Core/MyApp/App/studentstuff.c \
../Core/MyApp/App/taskcreate.c 

OBJS += \
./Core/MyApp/App/mutex.o \
./Core/MyApp/App/my_app.o \
./Core/MyApp/App/output.o \
./Core/MyApp/App/studentstuff.o \
./Core/MyApp/App/taskcreate.o 

C_DEPS += \
./Core/MyApp/App/mutex.d \
./Core/MyApp/App/my_app.d \
./Core/MyApp/App/output.d \
./Core/MyApp/App/studentstuff.d \
./Core/MyApp/App/taskcreate.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MyApp/App/%.o: ../Core/MyApp/App/%.c Core/MyApp/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-MyApp-2f-App

clean-Core-2f-MyApp-2f-App:
	-$(RM) ./Core/MyApp/App/mutex.d ./Core/MyApp/App/mutex.o ./Core/MyApp/App/my_app.d ./Core/MyApp/App/my_app.o ./Core/MyApp/App/output.d ./Core/MyApp/App/output.o ./Core/MyApp/App/studentstuff.d ./Core/MyApp/App/studentstuff.o ./Core/MyApp/App/taskcreate.d ./Core/MyApp/App/taskcreate.o

.PHONY: clean-Core-2f-MyApp-2f-App

