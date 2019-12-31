cmake_minimum_required(VERSION 3.13)
project(4chan-sdk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=modernize-*")

include_directories(/usr/include/libxml2)
include_directories(/usr/include/libxml++-3.0)
include_directories(/usr/lib/libxml++-3.0/include)

include_directories(/usr/include/glibmm-2.4)
include_directories(/usr/lib/glibmm-2.4/include)

include_directories(/usr/include/glib-2.0)
include_directories(/usr/lib/glib-2.0/include)

include_directories(lib/json)

include_directories(include)

file(GLOB sources "src/*.cpp")

add_library(4chansdk SHARED ${sources})
