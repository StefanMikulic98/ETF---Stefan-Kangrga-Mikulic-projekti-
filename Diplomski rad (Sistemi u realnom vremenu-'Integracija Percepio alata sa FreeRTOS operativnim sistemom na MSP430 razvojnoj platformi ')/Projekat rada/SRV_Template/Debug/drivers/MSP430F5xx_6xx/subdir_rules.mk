################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drivers/MSP430F5xx_6xx/%.obj: ../drivers/MSP430F5xx_6xx/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --data_model=restricted -Ooff --use_hw_mpy=F5 --include_path="C:/ti/ccs1230/ccs/ccs_base/msp430/include" --include_path="C:/Users/stefa/OneDrive/Documents/SRV_Template/Tracealyzer" --include_path="C:/Users/stefa/OneDrive/Documents/SRV_Template" --include_path="C:/Users/stefa/OneDrive/Documents/SRV_Template/drivers" --include_path="C:/Users/stefa/OneDrive/Documents/SRV_Template/FreeRTOS_source/include" --include_path="C:/Users/stefa/OneDrive/Documents/SRV_Template/FreeRTOS_source/portable/CCS/MSP430X" --include_path="C:/Users/stefa/OneDrive/Documents/SRV_Template" --include_path="C:/Users/stefa/OneDrive/Documents/SRV_Template/drivers/MSP430F5xx_6xx" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --include_path="C:/Users/stefa/OneDrive/Documents/SRV_Template/Tracealyzer/config" --include_path="C:/Users/stefa/OneDrive/Documents/SRV_Template/Tracealyzer/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="drivers/MSP430F5xx_6xx/$(basename $(<F)).d_raw" --obj_directory="drivers/MSP430F5xx_6xx" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

