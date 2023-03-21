cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(TARGET main)
set(SRCS main.cpp)

add_executable(${TARGET} ${SRCS})
target_compile_options(${TARGET} PUBLIC -O2 -g -std=gnu++17 -Wall -Wextra -Wpedantic)
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/include)
