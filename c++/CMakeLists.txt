cmake_minimum_required(VERSION 3.1)
project (camapp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(Boost REQUIRED COMPONENTS timer)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} capture.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES})