################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
utils/uartstdio.obj: /home/quynhpp/ti/tivaware_c_series_2_1_4_178/utils/uartstdio.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/quynhpp/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="/home/quynhpp/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" --include_path="/home/quynhpp/ti/tivaware_c_series_2_1_4_178/examples/boards/dk-tm4c123g" --include_path="/home/quynhpp/ti/tivaware_c_series_2_1_4_178" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PGE --define=TARGET_IS_TM4C123_RB1 --define=UART_BUFFERED --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="utils/$(basename $(<F)).d_raw" --obj_directory="utils" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

utils/ustdlib.obj: /home/quynhpp/ti/tivaware_c_series_2_1_4_178/utils/ustdlib.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/quynhpp/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="/home/quynhpp/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" --include_path="/home/quynhpp/ti/tivaware_c_series_2_1_4_178/examples/boards/dk-tm4c123g" --include_path="/home/quynhpp/ti/tivaware_c_series_2_1_4_178" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PGE --define=TARGET_IS_TM4C123_RB1 --define=UART_BUFFERED --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="utils/$(basename $(<F)).d_raw" --obj_directory="utils" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


