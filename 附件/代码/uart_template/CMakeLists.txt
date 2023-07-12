cmake_minimum_required(VERSION 3.1)
project(uart_template)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(PCL 1.10 REQUIRED COMPONENTS common io visualization)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PCL_INCLUDE_DIRS})
include_directories(uart)
include_directories(include)

IF(NOT WIN32)
    add_definitions(-Wno-format-extra-args)
    SET(SPECIAL_OS_LIBS "pthread" "X11")
ENDIF()

link_directories(${PCL_LIBRARY_DIRS})

add_definitions(${PCL_DEFINITIONS})

FILE(GLOB_RECURSE SRC_FILES src/*.cpp)
FILE(GLOB_RECURSE HDR_FILES include/*.hpp)

add_definitions(-std=c++17 -O2)

ADD_EXECUTABLE(uart_template main.cpp ${HDR_FILES} ${SRC_FILES})

target_link_libraries(uart_template ${OpenCV_LIBS})
target_link_libraries(uart_template Threads::Threads)
target_link_libraries(uart_template ${PCL_LIBRARIES})