cmake_minimum_required(VERSION 3.12)
project(quickjs-cpp CXX)

set (CMAKE_CXX_STANDARD 23)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(qjs src/qjs.cpp src/list.hpp src/cutils.cpp src/cutils.hpp)

target_include_directories(qjs PRIVATE ${PROJECT_SOURCE_DIR}/src)