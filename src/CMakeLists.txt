cmake_minimum_required(VERSION 3.5)

project(Forradia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

file(GLOB_RECURSE all_files
     "headers/*.h"
     "source/*.cpp"
)
 
link_directories(./lib C:/SDL2/lib/x86 C:/GLEW/lib/Release/Win32 C:/freeglut/lib)

add_executable(
    Forradia
    Main.cpp
    ${all_files})

# Linux
# target_link_libraries(Forradia GL GLU glut GLEW SDL2 SDL2_image SDL2_ttf)

# Windows
target_link_libraries(Forradia opengl32 GLEW32 SDL2 SDL2_image SDL2_ttf)

target_include_directories(Forradia PUBLIC . ./headers C:/SDL2/include C:/GLEW/include C:/freeglut/include)
