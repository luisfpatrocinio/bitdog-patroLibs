cmake_minimum_required(VERSION 3.14)
project(bitdogPatroLibs LANGUAGES C)

# Coleta recursiva de todos os arquivos fonte e headers
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB_RECURSE ALL_INCLUDES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# Coleta apenas os diretórios onde os headers estão (sem duplicar)
set(INCLUDE_DIRS "")
foreach(header ${ALL_INCLUDES})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# Cria a biblioteca estática
add_library(bitdogPatroLibs STATIC ${ALL_SOURCES})

# Expõe os headers para quem usar essa lib
target_include_directories(bitdogPatroLibs PUBLIC ${INCLUDE_DIRS})

# Link das bibliotecas padrão do PICO
target_link_libraries(bitdogPatroLibs
    pico_stdlib
    hardware_adc
    hardware_pwm
    hardware_i2c
)

# Se Wi-Fi estiver habilitado, linka o lwIP 
if(USE_WIFI)
    target_link_libraries(bitdogPatroLibs
        pico_cyw43_arch_lwip_threadsafe_background
    )
    target_compile_definitions(bitdogPatroLibs PRIVATE USE_WIFI)
endif()

# Cria alias para facilitar uso externo
add_library(bitdog::patrolibs ALIAS bitdogPatroLibs)
