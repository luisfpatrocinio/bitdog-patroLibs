cmake_minimum_required(VERSION 3.14)
project(bitdogPatroLibs LANGUAGES C)

# Primeiro coletamos todos os arquivos
file(GLOB_RECURSE ALL_SOURCES_CONFIGURE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB_RECURSE ALL_INCLUDES_CONFIGURE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# Filtramos os arquivos se Wi-Fi estiver desativado
if(NOT USE_WIFI)
    # Remove arquivos da pasta wifi
    set(ALL_SOURCES "")
    set(ALL_INCLUDES "")
    
    foreach(source ${ALL_SOURCES_CONFIGURE})
        if(NOT source MATCHES "/wifi/")
            list(APPEND ALL_SOURCES ${source})
        endif()
    endforeach()
    
    foreach(header ${ALL_INCLUDES_CONFIGURE})
        if(NOT header MATCHES "/wifi/")
            list(APPEND ALL_INCLUDES ${header})
        endif()
    endforeach()
else()
    set(ALL_SOURCES ${ALL_SOURCES_CONFIGURE})
    set(ALL_INCLUDES ${ALL_INCLUDES_CONFIGURE})
endif()

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

# Matriz de Led:
include(FetchContent)

# Incluindo bibliotecas externas no momento do build
FetchContent_Declare(
    ws2812b_animation
    GIT_REPOSITORY https://github.com/TuriSc/RP2040-WS2812B-Animation.git
    GIT_TAG main
)
FetchContent_MakeAvailable(ws2812b_animation)

# Link das bibliotecas padrão do PICO
target_link_libraries(bitdogPatroLibs
    pico_stdlib
    hardware_adc
    hardware_pwm
    hardware_i2c
    ws2812b_animation
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