cmake_minimum_required(VERSION 2.8)

project(rpi-ocv-vid)

find_package(OpenCV HINTS /opt/opencv3.1.0)
if(NOT OpenCV_FOUND)
  find_package(OpenCV 2.4.9 REQUIRED)
endif()

set(COMPILE_DEFINITIONS -Wall)
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
