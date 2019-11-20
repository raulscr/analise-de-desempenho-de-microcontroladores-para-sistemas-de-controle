################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/lib/pid_lib/qn_lib/q15lib.c \
D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/lib/pid_lib/qn_lib/q31lib.c \
D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/lib/pid_lib/qn_lib/q7lib.c 

OBJS += \
./pid_lib/qn_lib/q15lib.o \
./pid_lib/qn_lib/q31lib.o \
./pid_lib/qn_lib/q7lib.o 

C_DEPS += \
./pid_lib/qn_lib/q15lib.d \
./pid_lib/qn_lib/q31lib.d \
./pid_lib/qn_lib/q7lib.d 


# Each subdirectory must supply rules for building sources it contributes
pid_lib/qn_lib/q15lib.o: D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/lib/pid_lib/qn_lib/q15lib.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Inc" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/CMSIS/Include" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/lib/pid_lib"  -O0 -g3 -Wall -fmessage-length=0 -mlong-calls -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

pid_lib/qn_lib/q31lib.o: D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/lib/pid_lib/qn_lib/q31lib.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Inc" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/CMSIS/Include" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/lib/pid_lib"  -O0 -g3 -Wall -fmessage-length=0 -mlong-calls -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

pid_lib/qn_lib/q7lib.o: D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/lib/pid_lib/qn_lib/q7lib.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Inc" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/PID_STM32F1/Drivers/CMSIS/Include" -I"D:/analise-de-desempenho-de-microcontroladores-para-sistemas-de-controle/firmware/lib/pid_lib"  -O0 -g3 -Wall -fmessage-length=0 -mlong-calls -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


