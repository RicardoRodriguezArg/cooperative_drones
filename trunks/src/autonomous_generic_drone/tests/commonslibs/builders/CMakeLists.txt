project( test_builders )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
find_package(Threads REQUIRED)

#include (/home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/cmake/FindGMock.cmake)
find_package(GTest )
find_package(GMock )

include_directories (
                          /usr/local/lib
                        ${GTEST_INCLUDE_DIRS}
                        ${GMOCK_INCLUDE_DIRS}
                         ../../../../../src/autonomous_generic_drone/src/
                         ../../../../../src/autonomous_generic_drone/src/commonLibs
                         ../../../../../src/autonomous_generic_drone/src/commonLibs/builders
                        ../../../../../src/autonomous_generic_drone/src/commonLibs/tinyxml2
                        ../../../../../src/autonomous_generic_drone/src/commonLibs/netlink



                    )
set (HDR  
                ../../../../src/autonomous_generic_drone/src/commonLibs/tinyxml2/tinyxml2.cpp
                ../../../../src/autonomous_generic_drone/src/commonLibs/netlink/socket.cc
                builder_aux.h


        # ../../../ommonLibs/state_transition_unit.h
        # ../../../commonLibs/cmd_state_unit.h
        # ../../../commonLibs/events_state_traits.h

    )

set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_link_libraries(${PROJECT_NAME}
                                    -lpthread

                                    ${GTEST_LIBRARIES}
                                    ${GMOCK_BOTH_LIBRARIES}
                                    ${CMAKE_THREAD_LIBS_INIT}
)
