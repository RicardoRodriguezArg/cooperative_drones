project( kernel )
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
find_package( Threads )
include( ../../commonLibs/cmake/findGlog.cmake)
include_directories (
                                    ${GLOG_INCLUDE_DIR}
                                     ../
                                    ../../commonLibs
                                    ../../commonLibs/cmake
                                    ../../commonLibs/tinyxml2
                                    ../../commonLibs/netlink
                                   ../../commonLibs/utils_generics
                                    ../../commonLibs/factory
                                    ../../commonsLibs/Reactor
                                    ../cmd_processor

                                  )



set (HDR
                ../../commonLibs/tinyxml2/tinyxml2.cpp
                ../../commonLibs/netlink/socket.cc
                ../../commonLibs/factory/generic_factory.cpp
                 kernel.h
               
    )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

