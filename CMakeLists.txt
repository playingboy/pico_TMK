# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(picow_ble_keyboard C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

cmake_minimum_required(VERSION 3.13)

add_executable(picow_ble_keyboard)

target_sources(picow_ble_keyboard PUBLIC
        # ${CMAKE_CURRENT_LIST_DIR}/main.c
        # ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
        # ${CMAKE_CURRENT_LIST_DIR}/hid_keyboard_demo.c
        ${CMAKE_CURRENT_LIST_DIR}/hog_keyboard.c
        )

# Make sure TinyUSB can find tusb_config.h
target_include_directories(picow_ble_keyboard PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

pico_btstack_make_gatt_header(picow_ble_keyboard PRIVATE "${CMAKE_CURRENT_LIST_DIR}/hog_keyboard.gatt")

add_subdirectory(pico_keyboard)
 
# In addition to pico_stdlib required for common PicoSDK functionality
target_link_libraries(picow_ble_keyboard PUBLIC pico_stdlib pico_cyw43_arch_none pico_btstack_cyw43 pico_btstack_ble pico_keyboard)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
#target_compile_definitions(picow_ble_keyboard PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)

pico_add_extra_outputs(picow_ble_keyboard)

# add url via pico_set_program_url
