#-------------------------------------------------------------------------------
# CMake Setups
#-------------------------------------------------------------------------------
CMAKE_MINIMUM_REQUIRED (VERSION 3.15)

#-------------------------------------------------------------------------------
# Project Setups
#-------------------------------------------------------------------------------
PROJECT (UVA)
ENABLE_LANGUAGE(C CXX)

option(GTEST "Enable Google Test" OFF)

SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_ERROR_DEPRECATED ON)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS "-std=c++11 -O2")

if(GTEST)
  find_package(GTest CONFIG REQUIRED)
  ADD_DEFINITIONS("-DGTEST")
endif()

if(GTEST)
add_executable(test_runner unittest.cpp)
target_link_libraries(test_runner GTest::gtest)

else()
add_executable(main main.cpp)
endif()

