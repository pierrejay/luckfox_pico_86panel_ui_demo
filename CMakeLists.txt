cmake_minimum_required(VERSION 3.10)

set(SDK_PATH $ENV{LUCKFOX_SDK_PATH})
if(NOT SDK_PATH)
    message(WARNING "Please Set Luckfox-pico SDK Path. Such as:export LUCKFOX_SDK_PATH=/home/user/luckfox-pico")
    return()
endif()
set(CMAKE_C_COMPILER "${SDK_PATH}/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${SDK_PATH}/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-g++")

project(86UI_demo C)

set(CMAKE_C_FLAGS "-O3 -g0 -Wall -Wshadow -Wundef -Wmissing-prototypes \
    -Wno-discarded-qualifiers -Wextra -Wno-unused-function \
    -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing \
    -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized \
    -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits \
    -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual \
    -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar \
    -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare \
    -Wno-missing-prototypes -Wdouble-promotion -Wclobbered \
    -Wdeprecated -Wempty-body -Wshift-negative-value -Wstack-usage=2048 \
    -Wno-unused-value -Wno-format-overflow")
add_compile_options(-Wno-unused)

include_directories( 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/source
)

# lvgl
add_subdirectory(${CMAKE_SOURCE_DIR}/lvgl EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/lv_drivers EXCLUDE_FROM_ALL)

file(GLOB MAINSRC "${CMAKE_SOURCE_DIR}/*.c")
file(GLOB_RECURSE CSRCS "${CMAKE_SOURCE_DIR}/source/86panel_demo/*.c" 
                        "${CMAKE_SOURCE_DIR}/source/86panel_demo/fonts/*.c" 
                        "${CMAKE_SOURCE_DIR}/source/86panel_demo/images/*.c" 
                        "${CMAKE_SOURCE_DIR}/source/86panel_demo/screens/*.c")

add_executable(${PROJECT_NAME} ${MAINSRC} ${CSRCS})

target_link_libraries(${PROJECT_NAME}
    PRIVATE lvgl::drivers
    pthread
    m
)

install(TARGETS 86UI_demo DESTINATION bin)
