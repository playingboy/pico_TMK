# configure_file(config.h config.h)
add_library(phkb INTERFACE)
set(TMK_COMMON_DIR ${CMAKE_CURRENT_LIST_DIR}/../../tmk_core/common)
set(PICO_PR_SDK_DIR ${CMAKE_CURRENT_LIST_DIR}/../../pico_sdk)
# pico_generate_pio_header(pico_keyboard ${CMAKE_CURRENT_LIST_DIR}/keyboard.pio)
target_sources(phkb INTERFACE
    ${PICO_PR_SDK_DIR}/suspend.c
    ${PICO_PR_SDK_DIR}/printf.c
    ${PICO_PR_SDK_DIR}/timer.c
    ${PICO_PR_SDK_DIR}/bootloader.c
    ${PICO_PR_SDK_DIR}/xprintf.c
    ${CMAKE_CURRENT_LIST_DIR}/matrix.c
    ${CMAKE_CURRENT_LIST_DIR}/led.c
    ${CMAKE_CURRENT_LIST_DIR}/keymap_hhkb.c
    ${TMK_COMMON_DIR}/host.c
	${TMK_COMMON_DIR}/keyboard.c
	${TMK_COMMON_DIR}/matrix.c
	${TMK_COMMON_DIR}/action.c
    ${TMK_COMMON_DIR}/keymap.c
	${TMK_COMMON_DIR}/action_tapping.c
	${TMK_COMMON_DIR}/action_macro.c
	${TMK_COMMON_DIR}/action_layer.c
	${TMK_COMMON_DIR}/action_util.c
	${TMK_COMMON_DIR}/print.c
	${TMK_COMMON_DIR}/debug.c
	${TMK_COMMON_DIR}/util.c
	${TMK_COMMON_DIR}/hook.c
)

target_include_directories(phkb INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${TMK_COMMON_DIR}
    ${PICO_PR_SDK_DIR}
)

target_compile_options(phkb INTERFACE -include config.h)
message(STATUS "${COMPILE_OPTIONS} this is message!")

target_link_libraries(phkb INTERFACE)