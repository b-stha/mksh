cmake_minimum_required(VERSION 3.16)

project(mksh VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mksh
    src/main.cpp
    src/shell.cpp
    src/executor.cpp
)

target_include_directories(mksh PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(mksh PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)