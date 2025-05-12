cmake_minimum_required(VERSION 3.14)
project(bitdogPatroLibs LANGUAGES C)

# Lista todas as subpastas (assumidas como bibliotecas)
file(GLOB LIB_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */)

set(ALL_SOURCES "")
set(ALL_INCLUDES "")

foreach(dir ${LIB_DIRS})
    # Pega todos os .c e .h de cada lib
    file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.c)
    file(GLOB HDR_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.h)

    list(APPEND ALL_SOURCES ${SRC_FILES})
    list(APPEND ALL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
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
