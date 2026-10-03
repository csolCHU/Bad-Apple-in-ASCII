#This makes the requirement to use Cmake version 3.22 or higher
cmake_minimum_required(VERSION 3.22)

#Name of the project or names the project
project(BadApple)

#Uses C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Locates the directory of OpenCV Library
find_package(OpenCV REQUIRED)

#Compiles source code to .exe 
add_executable(BadApple badapple.cpp)

#Links program to OpenCV
target_link_libraries(BadApple PRIVATE ${OpenCV_LIBS})
