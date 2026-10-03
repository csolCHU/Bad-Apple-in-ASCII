#This makes the requirement to use Cmake version 3.22 or higher
cmake_minimum_required(VERSION 3.22)

project(BadApple)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(BadApple badapple.cpp)

target_include_directories(
    BadApple
    PRIVATE_HEADER
    ${OpenCV_LIBS}
)

target_link_libraries(BadApple PRIVATE ${OpenCV_LIBS} comdlg32)

if(WIN32)
    target_link_libraries(
        BadApple
        PRIVATE
        comdlg32
    )
endif()