project(unidad_sensores)
cmake_minimum_required( VERSION 2.8 )
set( CMAKE_BUILD_TYPE Debug )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")
find_package( Threads )
include_directories(../)
set (HDR 
         
)

add_executable (${PROJECT_NAME} main.cpp ${HDR} )
