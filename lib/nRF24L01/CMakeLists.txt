add_library(nrf24l01_lib
nRF24L01.cpp
nRF24L01.h
)

target_include_directories(nrf24l01_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(nrf24l01_lib
    pico_stdlib
    hardware_spi
    hardware_gpio
)