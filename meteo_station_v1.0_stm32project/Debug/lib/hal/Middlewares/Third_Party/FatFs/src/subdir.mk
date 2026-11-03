################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/hal/Middlewares/Third_Party/FatFs/src/diskio.c \
../lib/hal/Middlewares/Third_Party/FatFs/src/ff.c \
../lib/hal/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c 

C_DEPS += \
./lib/hal/Middlewares/Third_Party/FatFs/src/diskio.d \
./lib/hal/Middlewares/Third_Party/FatFs/src/ff.d \
./lib/hal/Middlewares/Third_Party/FatFs/src/ff_gen_drv.d 

OBJS += \
./lib/hal/Middlewares/Third_Party/FatFs/src/diskio.o \
./lib/hal/Middlewares/Third_Party/FatFs/src/ff.o \
./lib/hal/Middlewares/Third_Party/FatFs/src/ff_gen_drv.o 


# Each subdirectory must supply rules for building sources it contributes
lib/hal/Middlewares/Third_Party/FatFs/src/%.o lib/hal/Middlewares/Third_Party/FatFs/src/%.su lib/hal/Middlewares/Third_Party/FatFs/src/%.cyclo: ../lib/hal/Middlewares/Third_Party/FatFs/src/%.c lib/hal/Middlewares/Third_Party/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/libleguan/include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/CMSIS/Include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Core/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Middlewares/Third_Party/FatFs/src" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/USB_DEVICE/Target" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/USB_DEVICE/App" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/FATFS/App" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/FATFS/Target" -O0 -ffunction-sections -fdata-sections -Wall -Werror -mfp16-format=ieee -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-hal-2f-Middlewares-2f-Third_Party-2f-FatFs-2f-src

clean-lib-2f-hal-2f-Middlewares-2f-Third_Party-2f-FatFs-2f-src:
	-$(RM) ./lib/hal/Middlewares/Third_Party/FatFs/src/diskio.cyclo ./lib/hal/Middlewares/Third_Party/FatFs/src/diskio.d ./lib/hal/Middlewares/Third_Party/FatFs/src/diskio.o ./lib/hal/Middlewares/Third_Party/FatFs/src/diskio.su ./lib/hal/Middlewares/Third_Party/FatFs/src/ff.cyclo ./lib/hal/Middlewares/Third_Party/FatFs/src/ff.d ./lib/hal/Middlewares/Third_Party/FatFs/src/ff.o ./lib/hal/Middlewares/Third_Party/FatFs/src/ff.su ./lib/hal/Middlewares/Third_Party/FatFs/src/ff_gen_drv.cyclo ./lib/hal/Middlewares/Third_Party/FatFs/src/ff_gen_drv.d ./lib/hal/Middlewares/Third_Party/FatFs/src/ff_gen_drv.o ./lib/hal/Middlewares/Third_Party/FatFs/src/ff_gen_drv.su

.PHONY: clean-lib-2f-hal-2f-Middlewares-2f-Third_Party-2f-FatFs-2f-src

