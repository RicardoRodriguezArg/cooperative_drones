project( test_cmd_protocol )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
find_package(Threads REQUIRED)

include (/home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/cmake/FindGMock.cmake)
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

include_directories (
                        ../

                        /usr/local/lib
                        ${GTEST_INCLUDE_DIRS}
                        ${GMOCK_INCLUDE_DIRS}
                    )
set (HDR  
	../../../../src/autonomous_generic_drone/src/commonLibs/cmd_protocol/cmd_state_unit.h
        # ../../../ommonLibs/state_transition_unit.h
        # ../../../commonLibs/cmd_state_unit.h
        # ../../../commonLibs/events_state_traits.h
        cmd_state_aux.h
        cmd_state_test.h
    )

set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_link_libraries(${PROJECT_NAME}
                                    -lpthread

                                    ${GTEST_LIBRARIES}
                                    ${GMOCK_BOTH_LIBRARIES}
                                    ${CMAKE_THREAD_LIBS_INIT}
)
