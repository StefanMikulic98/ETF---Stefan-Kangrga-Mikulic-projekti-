################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/Device/SiliconLabs/EFM32GG/Source/system_efm32gg.c 

S_UPPER_SRCS += \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/Device/SiliconLabs/EFM32GG/Source/GCC/startup_efm32gg.S 

OBJS += \
./CMSIS/EFM32GG/startup_efm32gg.o \
./CMSIS/EFM32GG/system_efm32gg.o 

C_DEPS += \
./CMSIS/EFM32GG/system_efm32gg.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/EFM32GG/startup_efm32gg.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/Device/SiliconLabs/EFM32GG/Source/GCC/startup_efm32gg.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" '-DEFM32GG990F1024=1' -c -x assembler-with-cpp -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/EFM32GG/system_efm32gg.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/Device/SiliconLabs/EFM32GG/Source/system_efm32gg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"CMSIS/EFM32GG/system_efm32gg.d" -MT"CMSIS/EFM32GG/system_efm32gg.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


