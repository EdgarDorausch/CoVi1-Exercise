cmake_minimum_required(VERSION 3.17)
project(CoVi1_Exercises)

set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(CoVi1_Exercises exercise01.cpp)

target_link_libraries( CoVi1_Exercises ${OpenCV_LIBS} )

