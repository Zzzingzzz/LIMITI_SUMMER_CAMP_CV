CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(dnn_template)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

FILE(GLOB_RECURSE SRC_FILES src/*.cpp)
FILE(GLOB_RECURSE HDR_FILES include/*.hpp)

ADD_EXECUTABLE(run main.cpp ${HDR_FILES} ${SRC_FILES})
add_definitions(-std=c++14 -O2)

target_link_libraries(run ${OpenCV_LIBS})
