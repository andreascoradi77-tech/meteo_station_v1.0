################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/hal/USB_DEVICE/App/usb_device.c \
../lib/hal/USB_DEVICE/App/usbd_custom_hid_if.c \
../lib/hal/USB_DEVICE/App/usbd_desc.c 

C_DEPS += \
./lib/hal/USB_DEVICE/App/usb_device.d \
./lib/hal/USB_DEVICE/App/usbd_custom_hid_if.d \
./lib/hal/USB_DEVICE/App/usbd_desc.d 

OBJS += \
./lib/hal/USB_DEVICE/App/usb_device.o \
./lib/hal/USB_DEVICE/App/usbd_custom_hid_if.o \
./lib/hal/USB_DEVICE/App/usbd_desc.o 


# Each subdirectory must supply rules for building sources it contributes
lib/hal/USB_DEVICE/App/%.o lib/hal/USB_DEVICE/App/%.su lib/hal/USB_DEVICE/App/%.cyclo: ../lib/hal/USB_DEVICE/App/%.c lib/hal/USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/libleguan/include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/CMSIS/Include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Core/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/include" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/Middlewares/Third_Party/FatFs/src" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/USB_DEVICE/Target" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/USB_DEVICE/App" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/FATFS/App" -I"C:/BFH/meteo_station_v1.0/meteo_station_v1.0_stm32project/lib/hal/FATFS/Target" -O0 -ffunction-sections -fdata-sections -Wall -Werror -mfp16-format=ieee -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-hal-2f-USB_DEVICE-2f-App

clean-lib-2f-hal-2f-USB_DEVICE-2f-App:
	-$(RM) ./lib/hal/USB_DEVICE/App/usb_device.cyclo ./lib/hal/USB_DEVICE/App/usb_device.d ./lib/hal/USB_DEVICE/App/usb_device.o ./lib/hal/USB_DEVICE/App/usb_device.su ./lib/hal/USB_DEVICE/App/usbd_custom_hid_if.cyclo ./lib/hal/USB_DEVICE/App/usbd_custom_hid_if.d ./lib/hal/USB_DEVICE/App/usbd_custom_hid_if.o ./lib/hal/USB_DEVICE/App/usbd_custom_hid_if.su ./lib/hal/USB_DEVICE/App/usbd_desc.cyclo ./lib/hal/USB_DEVICE/App/usbd_desc.d ./lib/hal/USB_DEVICE/App/usbd_desc.o ./lib/hal/USB_DEVICE/App/usbd_desc.su

.PHONY: clean-lib-2f-hal-2f-USB_DEVICE-2f-App

