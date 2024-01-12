################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Main/OLED_I2C.c \
../Main/em_int.c \
../Main/lcd.c \
../Main/retargetvirtual.c 

OBJS += \
./Main/OLED_I2C.o \
./Main/em_int.o \
./Main/lcd.o \
./Main/retargetvirtual.o 

C_DEPS += \
./Main/OLED_I2C.d \
./Main/em_int.d \
./Main/lcd.d \
./Main/retargetvirtual.d 


# Each subdirectory must supply rules for building sources it contributes
Main/OLED_I2C.o: ../Main/OLED_I2C.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"Main/OLED_I2C.d" -MT"Main/OLED_I2C.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Main/em_int.o: ../Main/em_int.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"Main/em_int.d" -MT"Main/em_int.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Main/lcd.o: ../Main/lcd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"Main/lcd.d" -MT"Main/lcd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Main/retargetvirtual.o: ../Main/retargetvirtual.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"Main/retargetvirtual.d" -MT"Main/retargetvirtual.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


