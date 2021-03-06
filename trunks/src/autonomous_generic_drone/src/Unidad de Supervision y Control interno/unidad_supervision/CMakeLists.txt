project( unidad_supervision )
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
find_package( Threads )
include_directories (
                                   ../
                                   ../../commonLibs
                                   ../../commonLibs/cmake
                                   ../../commonLibs/tinyxml2
                                   ../../commonLibs/netlink
                                   ../../commonLibs/utils_generics
                                    ../../commonLibs/factory
                                    ../../commonLibs/Reactor
                                    ../kernel
                                    ../state_machine
                                    ../servers_service
                      )

include( ../../commonLibs/cmake/findGlog.cmake)
include_directories(${GLOG_INCLUDE_DIR}
                                )

set (HDR
                    ../../commonLibs/tinyxml2/tinyxml2.cpp
                    ../../commonLibs/netlink/socket.cc
                    ../../commonLibs/factory/generic_factory.cpp
                    ../../commonLibs/factory/factory_register.h
                    ../servers_service/servers_manager.h
	             
   )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
target_link_libraries( ${PROJECT_NAME}
                        ${CMAKE_THREAD_LIBS_INIT}
                         ${GLOG_LIBRARY}
                       )
