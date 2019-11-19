################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/qn_lib/q15lib.c \
../Inc/qn_lib/q31lib.c \
../Inc/qn_lib/q7lib.c 

OBJS += \
./Inc/qn_lib/q15lib.o \
./Inc/qn_lib/q31lib.o \
./Inc/qn_lib/q7lib.o 

C_DEPS += \
./Inc/qn_lib/q15lib.d \
./Inc/qn_lib/q31lib.d \
./Inc/qn_lib/q7lib.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/qn_lib/%.o: ../Inc/qn_lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/Raul/workspace/PID_STM32F4/Inc" -I"C:/Users/Raul/workspace/PID_STM32F4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Raul/workspace/PID_STM32F4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Raul/workspace/PID_STM32F4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Raul/workspace/PID_STM32F4/Drivers/CMSIS/Include" -I"C:/Users/Raul/workspace/PID_STM32F4/Inc/pid_lib"  -O0 -g3 -Wall -fmessage-length=0 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


