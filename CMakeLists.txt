cmake_minimum_required(VERSION 3.13)

set(NAME openheadphones)
include(pico_sdk_import.cmake)

project(openheadphones C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

set(PICO_SDK_PATH "/usr/share/pico-sdk")
set(PICO_BOARD pico CACHE STRING "Board type")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} pico_stdlib)

pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 0)

target_link_libraries(${PROJECT_NAME}
  hardware_spi
  hardware_i2c
  hardware_dma
  hardware_pio
  hardware_interp
  hardware_timer
  hardware_watchdog
  hardware_clocks
  hardware_pwm
)

pico_add_extra_outputs(${PROJECT_NAME})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.uf2
  DESTINATION .
)
