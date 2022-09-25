cmake_minimum_required(VERSION 3.22)
project(ch01)

include_directories(include)
link_directories(lib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(ch01 main.cpp )

target_link_libraries(ch01 libfreeglut.a opengl32.dll libglu32.a)