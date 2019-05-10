################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../OnethinxCore/OnethinxCore01.c 

OBJS += \
./OnethinxCore/OnethinxCore01.o 

C_DEPS += \
./OnethinxCore/OnethinxCore01.d 


# Each subdirectory must supply rules for building sources it contributes
OnethinxCore/%.o: ../OnethinxCore/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -DCY8C6347BZI_BLD53 -DDEBUG -DAPP_NAME='"HelloWorld_cm4"' -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/include" -I"C:\Users\Gebruiker\Desktop\HelloWorld\HelloWorld_mainapp\DemoKit" -I"C:\Users\Gebruiker\Desktop\HelloWorld\HelloWorld_mainapp\OnethinxCore" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/cmsis/include" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/include" -I"C:\Users\Gebruiker\Desktop\HelloWorld\HelloWorld_mainapp/GeneratedSource" -I"C:\Users\Gebruiker\Desktop\HelloWorld\HelloWorld_mainapp/Source" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/source" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_low" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/linker/cm4" -I"C:/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/cm0p/prebuilt" -std=gnu11 -mfpu=fpv4-sp-d16 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


