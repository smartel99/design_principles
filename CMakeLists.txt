cmake_minimum_required(VERSION 3.20)
project(design_patterns)

set(CMAKE_CXX_STANDARD 20)

add_executable(open_close principles/open_close.cpp)
add_executable(interface_segregation principles/interface_segregation.cpp)
add_executable(dependency_inversion principles/dependency_inversion.cpp)