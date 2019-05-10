################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/gcc/startup_psoc6_01_cm4.S 

OBJS += \
./psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/gcc/startup_psoc6_01_cm4.o 

S_UPPER_DEPS += \
./psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/gcc/startup_psoc6_01_cm4.d 


# Each subdirectory must supply rules for building sources it contributes
psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/gcc/%.o: ../psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/gcc/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -DCY8C6347BZI_BLD53 -DDEBUG -DAPP_NAME='"HelloWorld_cm4"' -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/include" -I"C:\Users\Gebruiker\Desktop\HelloWorld\HelloWorld_mainapp\DemoKit" -I"C:\Users\Gebruiker\Desktop\HelloWorld\HelloWorld_mainapp\OnethinxCore" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/cmsis/include" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/include" -I"C:\Users\Gebruiker\Desktop\HelloWorld\HelloWorld_mainapp/GeneratedSource" -I"C:\Users\Gebruiker\Desktop\HelloWorld\HelloWorld_mainapp/Source" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/source" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_low" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/linker/cm4" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/cm0p/prebuilt" -mfpu=fpv4-sp-d16 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


