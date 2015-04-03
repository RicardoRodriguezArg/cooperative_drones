project( kernel )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
include_directories (
                                     ../
                                   # /home/ricardo/Desktop/proyecto/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/
                                    ../../commonLibs
                                    ../../commonLibs/cmake
                                    ../../commonLibs/tinyxml2
                                    ../../commonLibs/netlink
                                   ../../commonsLibs/utils_generics

                                  )
include( ../../commonLibs/cmake/findGlog.cmake)
include_directories(${GLOG_INCLUDE_DIR}
                                )

set (HDR
                ../../commonLibs/tinyxml2/tinyxml2.cpp
                ../../commonLibs/netlink/socket.cc
                 kernel.h
               
    )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

