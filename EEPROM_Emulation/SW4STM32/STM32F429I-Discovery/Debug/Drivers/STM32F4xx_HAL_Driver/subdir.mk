################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c 

OBJS += \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_cortex.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_dma.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash_ex.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c_ex.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr_ex.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc_ex.o \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_spi.o 

C_DEPS += \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_cortex.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_dma.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash_ex.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c_ex.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr_ex.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc_ex.d \
./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_spi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_cortex.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_dma.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash_ex.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c_ex.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr_ex.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc_ex.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_spi.o: C:/Users/Sam/STM32CubeIDE/workspace2/EEPROM_Emulation/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c Drivers/STM32F4xx_HAL_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32F429I-Discovery -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32F4xx_HAL_Driver

clean-Drivers-2f-STM32F4xx_HAL_Driver:
	-$(RM) ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_cortex.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_cortex.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_cortex.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_dma.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_dma.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_dma.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash_ex.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash_ex.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_flash_ex.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_gpio.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c_ex.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c_ex.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_i2c_ex.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr_ex.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr_ex.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_pwr_ex.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc_ex.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc_ex.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_rcc_ex.su ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_spi.d ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_spi.o ./Drivers/STM32F4xx_HAL_Driver/stm32f4xx_hal_spi.su

.PHONY: clean-Drivers-2f-STM32F4xx_HAL_Driver

