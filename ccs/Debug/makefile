################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./uart_echo.obj" \
"./startup_ccs.obj" \
-l"libc.a" \
-l"C:/Luminary/StellarisWare_LM3S9B92/boards/ek-lm3s9b92/uart_bt/ccs/../../../../driverlib/ccs/Debug/driverlib.lib" \
"C:/Luminary/StellarisWare_LM3S9B92/boards/ek-lm3s9b92/uart_bt/uart_echo_ccs.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: uart_echo.out

dependents:
	-cd C:/Luminary/StellarisWare_LM3S9B92/driverlib/ccs/Debug && $(MAKE) clean all

# Tool invocations
uart_echo.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) C:/Luminary/StellarisWare_LM3S9B92/driverlib/ccs/Debug/driverlib.lib
	@echo 'Building target: $@'
	@echo 'Invoking: TMS470 Linker'
	"C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470/bin/cl470" -mv7M3 -g -O2 --gcc --define=ccs --define=PART_LM3S9B92 --define=TARGET_IS_TEMPEST_RB1 --diag_warning=225 -me --gen_func_subsections --abi=eabi --code_state=16 --ual -z -m"uart_echo_ccs.map" --stack_size=256 --heap_size=0 --warn_sections -i"C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470/lib" -i"C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470/include" --reread_libs --rom_model -o "uart_echo.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(TMS470_EXECUTABLE_OUTPUTS__QUOTED) "uart_echo.out"
	-$(RM) "startup_ccs.pp" "uart_echo.pp" 
	-$(RM) "startup_ccs.obj" "uart_echo.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-"C:/EC_FR/Code Composer Studio/ccsv5/utils/tiobj2bin/tiobj2bin.bat" "uart_echo.out" "uart_echo.bin" "C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470/bin/ofd470.exe" "C:/EC_FR/Code Composer Studio/ccsv5/tools/compiler/tms470/bin/hex470.exe" "C:/EC_FR/Code Composer Studio/ccsv5/utils/tiobj2bin/mkhex4bin.exe"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Luminary/StellarisWare_LM3S9B92/driverlib/ccs/Debug/driverlib.lib:

-include ../makefile.targets
