# GCC toolchain prefix

SET(TOOLCHAIN_PREFIX "/home/iwasz/local/share/arm-unknown-eabi" CACHE STRING "")
SET(TARGET_TRIPLET "arm-unknown-eabi" CACHE STRING "")
# As found in : Drivers/CMSIS/Device/ST/STM32F4xx/Include/stm32f4xx.h
SET(DEVICE "" CACHE STRING "")
SET(CUBE_ROOT "" CACHE STRING "")
SET(STARTUP_CODE "" CACHE STRING "")
SET(LINKER_SCRIPT "" CACHE STRING "")

SET(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)
SET(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PREFIX}/${TARGET_TRIPLET}/include)
SET(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PREFIX}/${TARGET_TRIPLET}/lib)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR arm)

SET(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-g++)
SET(CMAKE_ASM_COMPILER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-as")
SET(CMAKE_ASM-ATT_COMPILER "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-as")
SET(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-objcopy)
SET(CMAKE_OBJDUMP ${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-objdump)

SET(CMAKE_C_FLAGS "-std=gnu99 -fdata-sections -ffunction-sections -Wall" CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -fdata-sections -ffunction-sections -MD -Wall" CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_EXE_LINKER_FLAGS "-T ${LINKER_SCRIPT} -Wl,--gc-sections" CACHE INTERNAL "exe link flags")

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

INCLUDE_DIRECTORIES(${SUPPORT_FILES})
LINK_DIRECTORIES(${SUPPORT_FILES})
ADD_DEFINITIONS(-D${DEVICE})
INCLUDE_DIRECTORIES("${CUBE_ROOT}/Drivers/STM32F4xx_HAL_Driver/Inc/")
INCLUDE_DIRECTORIES("${CUBE_ROOT}/Drivers/CMSIS/Device/ST/STM32F4xx/Include/")
INCLUDE_DIRECTORIES("${CUBE_ROOT}/Drivers/CMSIS/Include/")

ENABLE_LANGUAGE (ASM-ATT)
