cmake_minimum_required(VERSION 3.14)
project(PlusLanguageInterpreter)

set(DEBUG ON)

set(CMAKE_PREFIX_PATH D:\\Qt630STATIC\\lib\\cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_INCLUDE_PATH})

string(TIMESTAMP BUILD_TIME %Y-%m-%d\ %H:%M:%S)
set(VERSION 1.3.7)
configure_file(include/config.h.in config.h)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEBUG)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)
endif(DEBUG)

file(GLOB_RECURSE PlusLanguageInterpreter_SRCS
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp

   ${CMAKE_INCLUDE_PATH}/*.hpp
)

add_executable(PlusLanguageInterpreter 
   WIN32
   resource.rc
   qrc.qrc
   ${CMAKE_INCLUDE_PATH}
   ${PlusLanguageInterpreter_SRCS}
)

if(DEBUG)
target_link_libraries(PlusLanguageInterpreter PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(PlusLanguageInterpreter PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(PlusLanguageInterpreter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
endif(DEBUG)