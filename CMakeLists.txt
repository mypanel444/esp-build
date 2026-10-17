cmake_minimum_required(VERSION 3.18)
project(esp_mod)
set(CMAKE_CXX_STANDARD 17)

add_library(esp SHARED main.cpp)
target_link_libraries(esp log dl)
