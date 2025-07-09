################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MyApp/App/ARM_keys.c \
../Core/MyApp/App/UART_keys.c \
../Core/MyApp/App/admin.c \
../Core/MyApp/App/gps.c \
../Core/MyApp/App/ledjes.c \
../Core/MyApp/App/student.c 

OBJS += \
./Core/MyApp/App/ARM_keys.o \
./Core/MyApp/App/UART_keys.o \
./Core/MyApp/App/admin.o \
./Core/MyApp/App/gps.o \
./Core/MyApp/App/ledjes.o \
./Core/MyApp/App/student.o 

C_DEPS += \
./Core/MyApp/App/ARM_keys.d \
./Core/MyApp/App/UART_keys.d \
./Core/MyApp/App/admin.d \
./Core/MyApp/App/gps.d \
./Core/MyApp/App/ledjes.d \
./Core/MyApp/App/student.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MyApp/App/%.o Core/MyApp/App/%.su Core/MyApp/App/%.cyclo: ../Core/MyApp/App/%.c Core/MyApp/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../Core/MyApp/App -I../Core/MyApp/Ports -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-MyApp-2f-App

clean-Core-2f-MyApp-2f-App:
	-$(RM) ./Core/MyApp/App/ARM_keys.cyclo ./Core/MyApp/App/ARM_keys.d ./Core/MyApp/App/ARM_keys.o ./Core/MyApp/App/ARM_keys.su ./Core/MyApp/App/UART_keys.cyclo ./Core/MyApp/App/UART_keys.d ./Core/MyApp/App/UART_keys.o ./Core/MyApp/App/UART_keys.su ./Core/MyApp/App/admin.cyclo ./Core/MyApp/App/admin.d ./Core/MyApp/App/admin.o ./Core/MyApp/App/admin.su ./Core/MyApp/App/gps.cyclo ./Core/MyApp/App/gps.d ./Core/MyApp/App/gps.o ./Core/MyApp/App/gps.su ./Core/MyApp/App/ledjes.cyclo ./Core/MyApp/App/ledjes.d ./Core/MyApp/App/ledjes.o ./Core/MyApp/App/ledjes.su ./Core/MyApp/App/student.cyclo ./Core/MyApp/App/student.d ./Core/MyApp/App/student.o ./Core/MyApp/App/student.su

.PHONY: clean-Core-2f-MyApp-2f-App

