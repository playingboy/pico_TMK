add_library(pico_keyboard INTERFACE)
pico_generate_pio_header(pico_keyboard ${CMAKE_CURRENT_LIST_DIR}/keyboard.pio)
target_sources(pico_keyboard INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/keyboard.c
)

target_include_directories(pico_keyboard INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(pico_keyboard INTERFACE
        hardware_pio
)