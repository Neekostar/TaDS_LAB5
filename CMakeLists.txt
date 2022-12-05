cmake_minimum_required(VERSION 3.24)
project(TaDS_LAB5)

set(CMAKE_CXX_STANDARD 17)

add_executable(TaDS_LAB5 main.cpp BMP/bmp.cpp BMP/bmp.h Menu/MyMenu.cpp Menu/MyMenu.h Menu/MyMenuItem.cpp Menu/MyMenuItem.h Errors/Errors.h Errors/Errors.cpp)
