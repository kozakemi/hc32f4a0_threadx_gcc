cmake_minimum_required(VERSION 3.27)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME hc32f4a0xi-template)

# Driver function selection
set(MCU_TYPE "HC32F4A0xI" CACHE STRING "Set MCU Type")
set(BOOTLOADER OFF CACHE BOOL "Set to ON if bootloader is enabled")
set(APP OFF CACHE BOOL "Set to ON if app is enabled")
set(RT-THREAD OFF CACHE BOOL "Set to ON if RT-Thread is enabled")

# ThreadX configuration
set(THREADX_ARCH "cortex_m4")
set(THREADX_TOOLCHAIN "gnu")

# Include toolchain file
include("drivers/toolchain/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME} VERSION 1.0.0)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})
# "Generate hex and bin files and associate them with the clean target."
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
    BYPRODUCTS 
        ${CMAKE_PROJECT_NAME}.hex
        ${CMAKE_PROJECT_NAME}.bin
)
# Include the drivers,Drivers can be loaded using the submodule management method, which is recommended.
add_subdirectory("drivers")

# Include ThreadX
add_subdirectory("middlewares/threadx-6.4.2_rel-segger")

set(DEFINES
    # Add user defines
)

file(GLOB SOURCES
    # Add user source files
    "${CMAKE_CURRENT_LIST_DIR}/src/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.S"
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SEGGER_RTT_V798d/RTT/SEGGER_RTT.c"
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SEGGER_RTT_V798d/RTT/SEGGER_RTT_printf.c"
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SEGGER_RTT_V798d/RTT/SEGGER_RTT_ASM_ARMv7M.S"
    "${CMAKE_CURRENT_LIST_DIR}/tools/nr_micro_shell-1.0.2/src/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/module/nr_micro_shell/src/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/src/module/segger_rtt/src/*.c"
    # SystemView source files
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/SEGGER/*.c"
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/SEGGER/*.S"
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.c"
    "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/Sample/ThreadX/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/Sample/ThreadX/Config/Cortex-M/*.c"
)

set(HEADERS
    # Add user headers
    "${CMAKE_CURRENT_LIST_DIR}/inc"
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SEGGER_RTT_V798d/RTT"
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SEGGER_RTT_V798d/Config"
    "${CMAKE_CURRENT_LIST_DIR}/src/module/nr_micro_shell/inc"
    "${CMAKE_CURRENT_LIST_DIR}/tools/nr_micro_shell-1.0.2/inc"
    "${CMAKE_CURRENT_LIST_DIR}/src/module/segger_rtt/inc"
    # SystemView header directories
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/SEGGER"
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/Config"
    # "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/Sample/ThreadX"
)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    ${DEFINES}
)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${SOURCES}
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${HEADERS}
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined libraries
    threadx
)

# Add SystemView header paths to ThreadX
target_include_directories(threadx INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/SEGGER"
    "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/Config"
    "${CMAKE_CURRENT_LIST_DIR}/tools/SystemView_Src_V360e/Sample/ThreadX"
)