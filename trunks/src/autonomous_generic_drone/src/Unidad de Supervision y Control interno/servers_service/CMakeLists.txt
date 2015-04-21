project( serves_service )
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
find_package( Threads )

include( ../../commonLibs/cmake/findGlog.cmake)
include_directories(${GLOG_INCLUDE_DIR})
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
                            ../../commonLibs/factory/generic_factory.cpp
                            servers_manager.h
                            #erver_manager.cpp
      )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_link_libraries( ${PROJECT_NAME}
                        ${CMAKE_THREAD_LIBS_INIT}
                         ${GLOG_LIBRARY}
                       )
