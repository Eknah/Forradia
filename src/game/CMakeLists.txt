cmake_minimum_required(VERSION 3.5)
project(Forradia LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")
file(GLOB_RECURSE all_files
     "*.h"
     "*.cpp"
)
add_executable(
    Forradia
    ../Main.cpp
    ${all_files}
)
target_link_libraries(Forradia GL GLU glut GLEW SDL2 SDL2_image SDL2_ttf)
target_include_directories(Forradia PUBLIC .)