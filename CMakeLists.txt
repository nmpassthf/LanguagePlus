cmake_minimum_required(VERSION 3.14)
project(pluslanguageparser)

set(DEBUG ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_INCLUDE_PATH})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEBUG)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
endif(DEBUG)

file(GLOB_RECURSE pluslanguageparser_SRCS
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp

   ${CMAKE_INCLUDE_PATH}/*.hpp
)

add_executable(pluslanguageparser 
#    WIN32
   ${CMAKE_INCLUDE_PATH}
   ${pluslanguageparser_SRCS}
)

if(DEBUG)
target_link_libraries(pluslanguageparser PRIVATE Qt${QT_VERSION_MAJOR}::Core)
endif(DEBUG)