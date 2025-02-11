<<<<<<< HEAD
# Generated Cmake Pico project file
=======

>>>>>>> b354dfeca69bcfb05bce31d0c51c177b17628ae1

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
<<<<<<< HEAD
set(PICO_BOARD pico_w CACHE STRING "Board type")
=======
set(PICO_BOARD pico CACHE STRING "Board type")
>>>>>>> b354dfeca69bcfb05bce31d0c51c177b17628ae1

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

<<<<<<< HEAD
project(pio_matrix C CXX ASM)
=======
project(DisplayC C CXX ASM)
>>>>>>> b354dfeca69bcfb05bce31d0c51c177b17628ae1

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

<<<<<<< HEAD
add_executable(pio_matrix pio_matrix.c ssd1306.c reboot.c led_matrix.c buzzer.c ) # Adiciona o arquivo .c 

pico_set_program_name(pio_matrix "pio_matrix")
pico_set_program_version(pio_matrix "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pio_matrix 0)
pico_enable_stdio_usb(pio_matrix 1)

pico_generate_pio_header(pio_matrix ${CMAKE_CURRENT_LIST_DIR}/pio_matrix.pio)

target_sources(pio_matrix PRIVATE
    pio_matrix.c
    reboot.c
    led_matrix.c
    buzzer.c
    ssd1306.c
    )

# Add the standard library to the build
target_link_libraries(pio_matrix PRIVATE
        pico_stdlib
        hardware_pio
	    hardware_adc
        hardware_pwm
        hardware_i2c
        pico_bootrom
        )

# Add the standard include files to the build
target_include_directories(pio_matrix PRIVATE
=======
add_executable(DisplayC DisplayC.c inc/ssd1306.c)

pico_set_program_name(DisplayC "DisplayC")
pico_set_program_version(DisplayC "0.1")
#pico_generate_pio_header(ws2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(DisplayC 0)
pico_enable_stdio_usb(DisplayC 1)

# Add the standard library to the build
target_link_libraries(DisplayC
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(DisplayC PRIVATE
>>>>>>> b354dfeca69bcfb05bce31d0c51c177b17628ae1
  ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
<<<<<<< HEAD
target_link_libraries(pio_matrix 
        
        )

pico_add_extra_outputs(pio_matrix)
=======
target_link_libraries(DisplayC 
        hardware_i2c
        )

pico_add_extra_outputs(DisplayC)

>>>>>>> b354dfeca69bcfb05bce31d0c51c177b17628ae1
