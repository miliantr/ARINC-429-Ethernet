cmake_minimum_required(VERSION 3.5)

project(BOLA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BOLA main.cpp arinc429.h arinc429.cpp enum.h)

install(TARGETS BOLA
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
