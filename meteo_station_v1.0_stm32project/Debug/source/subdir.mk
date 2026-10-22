################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/gui.cpp 

C_SRCS += \
../source/main.c 

C_DEPS += \
./source/main.d 

OBJS += \
./source/gui.o \
./source/main.o 

CPP_DEPS += \
./source/gui.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o source/%.su source/%.cyclo: ../source/%.cpp source/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../lib/hal/Core/Inc -I../lib/libleguan/include -I../lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc -I../lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../lib/hal/Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../lib/hal/Drivers/CMSIS/Include -I../lib/hal/FATFS/Target -I../lib/hal/FATFS/App -I../lib/hal/USB_DEVICE/App -I../lib/hal/USB_DEVICE/Target -I../lib/hal/Middlewares/Third_Party/FatFs/src -I../lib/hal/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../lib/hal/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
source/%.o source/%.su source/%.cyclo: ../source/%.c source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../lib/hal/Core/Inc -I../lib/libleguan/include -I../lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc -I../lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../lib/hal/Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../lib/hal/Drivers/CMSIS/Include -I../lib/hal/FATFS/Target -I../lib/hal/FATFS/App -I../lib/hal/USB_DEVICE/App -I../lib/hal/USB_DEVICE/Target -I../lib/hal/Middlewares/Third_Party/FatFs/src -I../lib/hal/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../lib/hal/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../include -O0 -ffunction-sections -fdata-sections -Wall -Werror -mfp16-format=ieee -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-source

clean-source:
	-$(RM) ./source/gui.cyclo ./source/gui.d ./source/gui.o ./source/gui.su ./source/main.cyclo ./source/main.d ./source/main.o ./source/main.su

.PHONY: clean-source

