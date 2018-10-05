cmake_minimum_required(VERSION 3.12)
project(TextThroughTime)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O2 -static-libgcc -static-libstdc++")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

file(GLOB SOURCE_FILES
        src/*.cpp src/*.h
        src/core/*.cpp src/core/*.h)

add_executable(TextThroughTime ${SOURCE_FILES})
target_link_libraries(TextThroughTime ${MINGW32_LIB})