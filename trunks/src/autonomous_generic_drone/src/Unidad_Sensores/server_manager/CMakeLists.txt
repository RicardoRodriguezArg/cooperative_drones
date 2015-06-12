project(server_manager)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
include_directories (
                                     ../
                                   ../../commonLibs
                                   ../../commonLibs/netlink
                                     ../../commonsLibs/factory
                                    ../../commonsLibs/Reactor
                                    )
set (HDR
                server_manager.h
    )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

