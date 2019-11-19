################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
pid_lib/qn_lib/q15lib.obj: C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q15lib.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmsp -Ooff --opt_for_speed=0 --use_hw_mpy=none --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib" --include_path="C:/Users/Raul/Dropbox/TCC/pid_lib" --include_path="C:/Users/Raul/workspace_v8/PID_MSP430" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --preinclude="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q15lib.h" --preinclude="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q31lib.h" --preinclude="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q7lib.h" --advice:power="all" --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="pid_lib/qn_lib/$(basename $(<F)).d_raw" --obj_directory="pid_lib/qn_lib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pid_lib/qn_lib/q31lib.obj: C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q31lib.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmsp -Ooff --opt_for_speed=0 --use_hw_mpy=none --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib" --include_path="C:/Users/Raul/Dropbox/TCC/pid_lib" --include_path="C:/Users/Raul/workspace_v8/PID_MSP430" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --preinclude="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q15lib.h" --preinclude="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q31lib.h" --preinclude="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q7lib.h" --advice:power="all" --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="pid_lib/qn_lib/$(basename $(<F)).d_raw" --obj_directory="pid_lib/qn_lib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pid_lib/qn_lib/q7lib.obj: C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q7lib.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmsp -Ooff --opt_for_speed=0 --use_hw_mpy=none --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib" --include_path="C:/Users/Raul/Dropbox/TCC/pid_lib" --include_path="C:/Users/Raul/workspace_v8/PID_MSP430" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --preinclude="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q15lib.h" --preinclude="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q31lib.h" --preinclude="C:/Users/Raul/Dropbox/TCC/pid_lib/qn_lib/q7lib.h" --advice:power="all" --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="pid_lib/qn_lib/$(basename $(<F)).d_raw" --obj_directory="pid_lib/qn_lib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


