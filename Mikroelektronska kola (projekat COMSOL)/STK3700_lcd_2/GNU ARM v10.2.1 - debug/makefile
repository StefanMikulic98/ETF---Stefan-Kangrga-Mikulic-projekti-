################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include emlib/subdir.mk
-include Main/subdir.mk
-include Drivers/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include BSP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: STK3700_lcd_2.axf

# Tool invocations
STK3700_lcd_2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "STK3700_lcd_2.ld" -Xlinker --gc-sections -Xlinker -Map="STK3700_lcd_2.map" --specs=nano.specs -o STK3700_lcd_2.axf "./BSP/bsp_bcc.o" "./BSP/bsp_stk.o" "./BSP/bsp_stk_leds.o" "./BSP/bsp_trace.o" "./CMSIS/EFM32GG/startup_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./Drivers/retargetio.o" "./Drivers/segmentlcd.o" "./Drivers/vddcheck.o" "./Main/OLED_I2C.o" "./Main/em_int.o" "./Main/lcd.o" "./Main/retargetvirtual.o" "./emlib/em_adc.o" "./emlib/em_assert.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_ebi.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_lcd.o" "./emlib/em_leuart.o" "./emlib/em_prs.o" "./emlib/em_rtc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/em_vcmp.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: STK3700_lcd_2.hex'
	arm-none-eabi-objcopy -O ihex "STK3700_lcd_2.axf" "STK3700_lcd_2.hex"
	@echo ' '

	@echo 'Building bin file: STK3700_lcd_2.bin'
	arm-none-eabi-objcopy -O binary "STK3700_lcd_2.axf" "STK3700_lcd_2.bin"
	@echo ' '

	@echo 'Building s37 file: STK3700_lcd_2.s37'
	arm-none-eabi-objcopy -O srec "STK3700_lcd_2.axf" "STK3700_lcd_2.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "STK3700_lcd_2.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) STK3700_lcd_2.axf
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
