project( unidad_supervision )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
find_package( Threads )
include_directories (
                                   ../
                                   ../../commonLibs
                                   ../../commonLibs/cmake
                                   ../../commonLibs/tinyxml2
                                   ../../commonLibs/netlink
                                   ../../commonsLibs/utils_generics
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
	             
   )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
target_link_libraries( ${PROJECT_NAME}
                        ${CMAKE_THREAD_LIBS_INIT}
                         ${GLOG_LIBRARY}
                       )
