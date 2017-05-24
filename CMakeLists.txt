CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET (CMAKE_VERBOSE_MAKEFILE OFF)

PROJECT (gp8-clock)
include (stm32.cmake)

INCLUDE_DIRECTORIES("src/")

# +-----------------+
# | My code         |
# +-----------------+
SET (APP_SOURCES
        "src/main.cc"
        "src/I2CLcdDataLink.cc"
        "src/I2CLcdDataLink.h"
        "src/utils.cc"
        "src/utils.h"
        "src/Timer.cc"
        "src/Timer.h"
        "src/Buzzer.cc"
        "src/Buzzer.h"
        "src/Debug.cc"
        "src/Debug.h"
        "src/Adc.cc"
        "src/Adc.h"
        "src/AdcChannel.cc"
        "src/AdcChannel.h"
        "src/StopWatch.cc"
        "src/StopWatch.h"
        "src/InfraRedBeam.cc"
        "src/InfraRedBeam.h"
        "src/History.cc"
        "src/History.h"
        "src/FastStateMachine.cc"
        "src/FastStateMachine.h"
        "src/IDisplay.h"
        "src/ILcdDataLink.h"
        "src/ILcdDdriver.h"
        "src/PCF85176Driver.cc"
        "src/PCF85176Driver.h"
        "src/T145003.cc"
        "src/T145003.h"
        "src/stm32f4xx_it.c"
        "src/syscalls.c"
        "src/system_stm32f0xx.c"
        "src/stm32f0xx_hal_conf.h"
        "src/config-proto0.h"
        "src/config.h"

# +--------------+
# | STM Cube     |
# +--------------+
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_adc_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_can.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cec.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_comp.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_crc.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_crc_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dac.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dac_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2s.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_irda.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_iwdg.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_msp_template.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rtc.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rtc_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smartcard.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smartcard_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_smbus.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_spi.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_spi_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tsc.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart_ex.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_usart.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_wwdg.c"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_uart_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_iwdg.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_rcc.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_def.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_pwr_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_i2c.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_uart.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_smartcard.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_i2c_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_pcd.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_wwdg.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_i2s.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_tsc.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_usart.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_rtc.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_adc_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_crc.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_pwr.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_dac_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_irda_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_flash.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_tim_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_dma.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_irda.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_smbus.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_adc.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_spi_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_tim.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_can.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_cec.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_rcc_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_pcd_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_gpio.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_flash_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_comp.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_dac.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_conf_template.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_dma_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_usart_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_spi.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_smartcard_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_gpio_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_crc_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_rtc_ex.h"
        "${CUBE_ROOT}/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_cortex.h"

        "${STARTUP_CODE}")


ADD_DEFINITIONS ("-DHSE_VALUE=${CRYSTAL_HZ}")

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${APP_SOURCES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME}.elf stdc++)

SET (CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-objcopy)
SET (CMAKE_OBJDUMP ${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-objdump)
ADD_CUSTOM_TARGET(${CMAKE_PROJECT_NAME}.bin ALL DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin)

FIND_PROGRAM (ST_FLASH st-flash)
ADD_CUSTOM_TARGET("upload" DEPENDS ${CMAKE_PROJECT_NAME}.elf COMMAND ${ST_FLASH} --reset write ${CMAKE_PROJECT_NAME}.bin 0x8000000)
