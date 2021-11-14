# CMakeList.txt : CMake project for Calculator_with_dll, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
# Add source to this project's executable.
add_executable (Calculator_with_dll "Calculator_with_dll.cpp" "Calculator_with_dll.h" "Calculator.cpp" "Calculator.h" "Parser.cpp" "Parser.h" "InfoFunc.h")

# TODO: Add tests and install targets if needed.
