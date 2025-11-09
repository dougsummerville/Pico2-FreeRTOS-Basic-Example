cmake_minimum_required(VERSION 3.13)

set (PICO_BOARD "pico2")
set (PICO_PLATFORM "rp2350-arm-s")
set (PICO_SDK_PATH "~/pico-sdk")
set (FREERTOS_KERNEL_PATH "~/FreeRTOS-Kernel")
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2350_ARM_NTZ/FreeRTOS_Kernel_import.cmake)
#add_subdirectory(/home/dsummer/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2350_ARM_NTZ FREERTOS_KERNEL)

set(FREERTOS_CONFIG_FILE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})



project(example C CXX)
set(CMAKE_C_STANDARD 11)

pico_sdk_init()

add_executable(main
        main.c
        )

	pico_enable_stdio_usb(main 1) 
	pico_enable_stdio_uart(main 0)

	target_link_libraries( main
		FreeRTOS-Kernel
		pico_stdlib
		pico_stdio_usb
	)
pico_add_extra_outputs(main)
