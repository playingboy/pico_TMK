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

project(picow_ble_hid_keyboard C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(picow_ble_hid_keyboard
    picow_ble_hid_keyboard.c
    btstack_hog_kb.c)

target_sources(picow_ble_hid_keyboard PUBLIC
    # ${CMAKE_CURRENT_LIST_DIR}/main.c
    # ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
    # ${CMAKE_CURRENT_LIST_DIR}/hid_keyboard_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/hog_keyboard_main.c
    ${CMAKE_CURRENT_LIST_DIR}/hog_keyboard_tmk.c
    ${CMAKE_CURRENT_LIST_DIR}/tmk_core/common/keyboard.c
    )

pico_set_program_name(picow_ble_hid_keyboard "picow_ble_hid_keyboard")
pico_set_program_version(picow_ble_hid_keyboard "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(picow_ble_hid_keyboard 0)
pico_enable_stdio_usb(picow_ble_hid_keyboard 0)


# add_subdirectory(tmk_core)
add_subdirectory(keyboard/phkb)
# Add the standard library to the build
target_link_libraries(picow_ble_hid_keyboard
        pico_stdlib
        pico_util
        pico_cyw43_arch_none
        pico_btstack_cyw43
        pico_btstack_ble
        phkb
)

# Add the standard include files to the build
target_include_directories(picow_ble_hid_keyboard PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/keyboard/phkb
        ${CMAKE_CURRENT_LIST_DIR}/tmk_core
)
pico_btstack_make_gatt_header(picow_ble_hid_keyboard PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/picow_ble_hid_keyboard.gatt")

pico_add_extra_outputs(picow_ble_hid_keyboard)

