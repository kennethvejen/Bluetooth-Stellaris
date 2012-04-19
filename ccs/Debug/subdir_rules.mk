################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
startup_ccs.obj: C:/Luminary/StellarisWare_LM3S9B92/boards/ek-lm3s9b92/uart_bt/startup_ccs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: TMS470 Compiler'
	"C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470/bin/cl470" -mv7M3 -g -O2 --gcc --define=ccs --define=PART_LM3S9B92 --define=TARGET_IS_TEMPEST_RB1 --include_path="C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470/include" --include_path="C:/Luminary/StellarisWare_LM3S9B92/boards/ek-lm3s9b92/uart_bt/ccs/../../../.." --diag_warning=225 -me --gen_func_subsections --abi=eabi --code_state=16 --ual --preproc_with_compile --preproc_dependency="startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_echo.obj: C:/Luminary/StellarisWare_LM3S9B92/boards/ek-lm3s9b92/uart_bt/uart_echo.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: TMS470 Compiler'
	"C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470/bin/cl470" -mv7M3 -g -O2 --gcc --define=ccs --define=PART_LM3S9B92 --define=TARGET_IS_TEMPEST_RB1 --include_path="C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470/include" --include_path="C:/Luminary/StellarisWare_LM3S9B92/boards/ek-lm3s9b92/uart_bt/ccs/../../../.." --diag_warning=225 -me --gen_func_subsections --abi=eabi --code_state=16 --ual --preproc_with_compile --preproc_dependency="uart_echo.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


