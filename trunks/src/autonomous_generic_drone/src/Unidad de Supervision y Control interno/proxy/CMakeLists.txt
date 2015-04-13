project( proxy )
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
include_directories (
                                   ../
                                   ../../commonLibs
                                   ../../commonLibs/tinyxml2
                                   ../../commonLibs/netlink
                                   ../../commonsLibs/utils_generics
                                    ../../commonsLibs/factory
                                    ../../commonsLibs/Reactor
				    ../../commonsLibs/proxy_base


                                  )
set (HDR
                            ../../commonLibs/tinyxml2/tinyxml2.cpp
                            ../../commonLibs/netlink/socket.cc
                            proxy.h
                            
      )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

