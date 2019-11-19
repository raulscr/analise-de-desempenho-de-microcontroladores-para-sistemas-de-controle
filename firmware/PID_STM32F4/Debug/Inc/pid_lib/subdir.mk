################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/pid_lib/pidlib.c 

OBJS += \
./Inc/pid_lib/pidlib.o 

C_DEPS += \
./Inc/pid_lib/pidlib.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/pid_lib/%.o: ../Inc/pid_lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/Raul/workspace/PID_STM32F4/Inc" -I"C:/Users/Raul/workspace/PID_STM32F4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Raul/workspace/PID_STM32F4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Raul/workspace/PID_STM32F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Raul/workspace/PID_STM32F4/Drivers/CMSIS/Include" -I"C:/Users/Raul/workspace/PID_STM32F4/Inc/pid_lib"  -O0 -g3 -Wall -fmessage-length=0 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


