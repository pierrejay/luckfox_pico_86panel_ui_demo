cmake_minimum_required(VERSION 3.10)

set(SDK_PATH $ENV{LUCKFOX_SDK_PATH})
if(NOT SDK_PATH)
    message(WARNING "Please Set Luckfox-pico SDK Path. Such as:export LUCKFOX_SDK_PATH=/home/user/luckfox-pico")
    return()
endif()
set(CMAKE_C_COMPILER "${SDK_PATH}/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${SDK_PATH}/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-g++")

# Projet principal
project(luckfox_panel86 C CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-O3 -g0 -Wall -Wno-shadow -Wundef -Wmissing-prototypes \
    -Wno-discarded-qualifiers -Wextra -Wno-unused-function \
    -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing \
    -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized \
    -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits \
    -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual \
    -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar \
    -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare \
    -Wno-missing-prototypes -Wno-double-promotion -Wclobbered \
    -Wdeprecated -Wempty-body -Wshift-negative-value -Wstack-usage=2048 \
    -Wno-unused-value -Wno-format-overflow")

set(CMAKE_CXX_FLAGS "-O3 -g0 -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare \
    -Wno-unused-value -fno-strict-aliasing")

add_compile_options(-Wno-unused)

include_directories( 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/source
    ${CMAKE_SOURCE_DIR}/source/thermostat_app
)

# lvgl
add_subdirectory(${CMAKE_SOURCE_DIR}/lvgl EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/lv_drivers EXCLUDE_FROM_ALL)

# libmodbus est requis (plus de simulation)
set(LIBMODBUS_DIR "${CMAKE_SOURCE_DIR}/lib/libmodbus_arm")
if(NOT EXISTS "${LIBMODBUS_DIR}/lib/libmodbus.a")
    message(FATAL_ERROR "libmodbus requis! Placez lib/libmodbus_arm/ dans le répertoire racine")
endif()
message(STATUS "libmodbus trouvé: ${LIBMODBUS_DIR}")

#======================================
# THERMOSTAT APPLICATION (LVGL + EEZ + Modbus)
#======================================

# Sources thermostat (C++ main + C++ class + C bridge + C UI)
file(GLOB THERMOSTAT_MAIN "${CMAKE_SOURCE_DIR}/main.cpp")
file(GLOB THERMOSTAT_CPP_SRCS 
    "${CMAKE_SOURCE_DIR}/source/thermostat_app/*.cpp")
file(GLOB_RECURSE THERMOSTAT_C_SRCS 
    "${CMAKE_SOURCE_DIR}/source/thermostat_ui/*.c" 
    "${CMAKE_SOURCE_DIR}/source/thermostat_ui/ui/*.c")

add_executable(thermostat_demo ${THERMOSTAT_MAIN} ${THERMOSTAT_CPP_SRCS} ${THERMOSTAT_C_SRCS})

target_link_libraries(thermostat_demo
    PRIVATE lvgl::drivers
    pthread
    m
)

# Ajouter libmodbus au thermostat (toujours)
target_include_directories(thermostat_demo PRIVATE ${LIBMODBUS_DIR}/include)
target_link_libraries(thermostat_demo PRIVATE ${LIBMODBUS_DIR}/lib/libmodbus.a)
message(STATUS "Thermostat: avec libmodbus")


#======================================
# INSTALLATION
#======================================

install(TARGETS thermostat_demo
        DESTINATION bin)