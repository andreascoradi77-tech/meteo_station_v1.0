################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/hal/Middlewares/Third_Party/FatFs/src/option/syscall.c 

C_DEPS += \
./lib/hal/Middlewares/Third_Party/FatFs/src/option/syscall.d 

OBJS += \
./lib/hal/Middlewares/Third_Party/FatFs/src/option/syscall.o 


# Each subdirectory must supply rules for building sources it contributes
lib/hal/Middlewares/Third_Party/FatFs/src/option/%.o lib/hal/Middlewares/Third_Party/FatFs/src/option/%.su lib/hal/Middlewares/Third_Party/FatFs/src/option/%.cyclo: ../lib/hal/Middlewares/Third_Party/FatFs/src/option/%.c lib/hal/Middlewares/Third_Party/FatFs/src/option/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/libleguan/include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/CMSIS/Include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Core/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Middlewares/Third_Party/FatFs/src" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/USB_DEVICE/Target" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/USB_DEVICE/App" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/FATFS/App" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/FATFS/Target" -O0 -ffunction-sections -fdata-sections -Wall -Werror -mfp16-format=ieee -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-hal-2f-Middlewares-2f-Third_Party-2f-FatFs-2f-src-2f-option

clean-lib-2f-hal-2f-Middlewares-2f-Third_Party-2f-FatFs-2f-src-2f-option:
	-$(RM) ./lib/hal/Middlewares/Third_Party/FatFs/src/option/syscall.cyclo ./lib/hal/Middlewares/Third_Party/FatFs/src/option/syscall.d ./lib/hal/Middlewares/Third_Party/FatFs/src/option/syscall.o ./lib/hal/Middlewares/Third_Party/FatFs/src/option/syscall.su

.PHONY: clean-lib-2f-hal-2f-Middlewares-2f-Third_Party-2f-FatFs-2f-src-2f-option

