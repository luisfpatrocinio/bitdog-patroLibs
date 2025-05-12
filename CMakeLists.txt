cmake_minimum_required(VERSION 3.14)
project(bitdogPatroLibs LANGUAGES C)

# Lista todas as subpastas (assumidas como bibliotecas)
file(GLOB ALL_ITEMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

set(LIB_DIRS "")
foreach(item ${ALL_ITEMS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${item}")
        list(APPEND LIB_DIRS ${item})
    endif()
endforeach()


# Cria uma biblioteca estática com tudo
add_library(bitdogPatroLibs STATIC ${ALL_SOURCES})

# Expõe os headers para quem usar essa lib
target_include_directories(bitdogPatroLibs PUBLIC ${ALL_INCLUDES})

# Link necessary Pico SDK hardware libraries to enable use of peripherals
# such as ADC, PWM, and I2C within the bitdogPatroLibs target.
target_link_libraries(bitdogPatroLibs
    pico_stdlib
    hardware_adc
    hardware_pwm
    hardware_i2c
)

# Cria um alias com namespace
add_library(bitdog::patrolibs ALIAS bitdogPatroLibs)
