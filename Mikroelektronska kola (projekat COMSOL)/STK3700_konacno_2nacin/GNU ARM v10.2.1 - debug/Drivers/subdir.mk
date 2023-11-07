################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/hardware/kit/common/drivers/retargetio.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/hardware/kit/common/drivers/segmentlcd.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/hardware/kit/common/drivers/vddcheck.c 

OBJS += \
./Drivers/retargetio.o \
./Drivers/segmentlcd.o \
./Drivers/vddcheck.o 

C_DEPS += \
./Drivers/retargetio.d \
./Drivers/segmentlcd.d \
./Drivers/vddcheck.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/retargetio.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/hardware/kit/common/drivers/retargetio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"Drivers/retargetio.d" -MT"Drivers/retargetio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/segmentlcd.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/hardware/kit/common/drivers/segmentlcd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"Drivers/segmentlcd.d" -MT"Drivers/segmentlcd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/vddcheck.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/hardware/kit/common/drivers/vddcheck.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"Drivers/vddcheck.d" -MT"Drivers/vddcheck.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


