cmake_minimum_required(VERSION 3.17)
project(Diff)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_CXX_STANDARD 20)


include_directories(.)

find_library(hopsancore, "C:/Program Files (x86)/Hopsan")
find_library(hopsancore, "C:/Program File/Hopsan")

include_directories("C:/Program Files (x86)/Hopsan/HopsanCore/include")
include_directories("C:/Program Files/Hopsan/HopsanCore/include")




LINK_DIRECTORIES("C:/Program Files (x86)/Hopsan/lib")
LINK_DIRECTORIES("C:/Program Files (x86)/Hopsan/bin")

LINK_DIRECTORIES("C:/Program Files/Hopsan/lib")
LINK_DIRECTORIES("C:/Program Files/Hopsan/bin")
add_definitions(-DHOPSAN_BUILD_TYPE_RELEASE -DHOPSANCORE_DLLIMPORT -fPIC)

link_libraries(hopsancore)

add_library(Diff SHARED
        Diff.cpp)
