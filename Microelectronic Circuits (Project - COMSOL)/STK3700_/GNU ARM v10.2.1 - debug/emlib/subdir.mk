################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_adc.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_assert.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_cmu.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_core.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_ebi.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_emu.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_gpio.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_i2c.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_lcd.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_leuart.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_prs.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_rtc.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_system.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_timer.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_usart.c \
C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_vcmp.c 

OBJS += \
./emlib/em_adc.o \
./emlib/em_assert.o \
./emlib/em_cmu.o \
./emlib/em_core.o \
./emlib/em_ebi.o \
./emlib/em_emu.o \
./emlib/em_gpio.o \
./emlib/em_i2c.o \
./emlib/em_lcd.o \
./emlib/em_leuart.o \
./emlib/em_prs.o \
./emlib/em_rtc.o \
./emlib/em_system.o \
./emlib/em_timer.o \
./emlib/em_usart.o \
./emlib/em_vcmp.o 

C_DEPS += \
./emlib/em_adc.d \
./emlib/em_assert.d \
./emlib/em_cmu.d \
./emlib/em_core.d \
./emlib/em_ebi.d \
./emlib/em_emu.d \
./emlib/em_gpio.d \
./emlib/em_i2c.d \
./emlib/em_lcd.d \
./emlib/em_leuart.d \
./emlib/em_prs.d \
./emlib/em_rtc.d \
./emlib/em_system.d \
./emlib/em_timer.d \
./emlib/em_usart.d \
./emlib/em_vcmp.d 


# Each subdirectory must supply rules for building sources it contributes
emlib/em_adc.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_adc.d" -MT"emlib/em_adc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_assert.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_assert.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_assert.d" -MT"emlib/em_assert.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_cmu.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_cmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_cmu.d" -MT"emlib/em_cmu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_core.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_core.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_core.d" -MT"emlib/em_core.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_ebi.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_ebi.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_ebi.d" -MT"emlib/em_ebi.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_emu.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_emu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_emu.d" -MT"emlib/em_emu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_gpio.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_gpio.d" -MT"emlib/em_gpio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_i2c.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_i2c.d" -MT"emlib/em_i2c.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_lcd.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_lcd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_lcd.d" -MT"emlib/em_lcd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_leuart.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_leuart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_leuart.d" -MT"emlib/em_leuart.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_prs.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_prs.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_prs.d" -MT"emlib/em_prs.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_rtc.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_rtc.d" -MT"emlib/em_rtc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_system.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_system.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_system.d" -MT"emlib/em_system.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_timer.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_timer.d" -MT"emlib/em_timer.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_usart.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_usart.d" -MT"emlib/em_usart.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_vcmp.o: C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_vcmp.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/EFM32GG_STK3700/config" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Include" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/bsp" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//hardware/kit/common/drivers" -I"C:/Users/stefa/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFM32GG/Include" -O2 -Wall -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP -MF"emlib/em_vcmp.d" -MT"emlib/em_vcmp.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


