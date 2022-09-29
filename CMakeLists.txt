cmake_minimum_required(VERSION 3.14)
project(pluslanguageparser)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_INCLUDE_PATH})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE pluslanguageparser_SRCS
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp

   ${CMAKE_INCLUDE_PATH}/*.hpp
)

add_executable(pluslanguageparser 
#    WIN32
   ${CMAKE_INCLUDE_PATH}
   ${pluslanguageparser_SRCS}
)
