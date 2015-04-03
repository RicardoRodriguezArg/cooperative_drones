project( serves_service )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
include_directories (
                                   ../
                                   ../../commonLibs
                                   ../../commonLibs/tinyxml2
                                   ../../commonLibs/netlink
                                   ../../commonsLibs/utils_generics
                                    ../../commonsLibs/factory
                                    ../../commonsLibs/Reactor

                                  )
set (HDR
                            ../../commonLibs/tinyxml2/tinyxml2.cpp
                            ../../commonLibs/netlink/socket.cc
                            servers_manager.h
      )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

