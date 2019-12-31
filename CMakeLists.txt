cmake_minimum_required(VERSION 3.13)
project(4chan-sdk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=modernize-*")

include_directories(include)

file(GLOB sources "src/*.cpp")

add_library(4chansdk SHARED ${sources})
