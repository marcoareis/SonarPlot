cmake_minimum_required(VERSION 2.8)
PROJECT(my_project)
FIND_PACKAGE(OpenCV REQUIRED)
ADD_EXECUTABLE(teste1 main.cpp)
TARGET_LINK_LIBRARIES(teste1 ${OpenCV_LIBS})

