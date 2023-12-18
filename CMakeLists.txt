cmake_minimum_required(VERSION 3.24)
project(SDL)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR C:/lib/SDL/include)
set(SDL2_LIB_DIR C:/lib/SDL/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(SDL main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
