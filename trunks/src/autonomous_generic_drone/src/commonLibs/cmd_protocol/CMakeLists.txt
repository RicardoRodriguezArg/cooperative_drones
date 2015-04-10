project( cmd_protocol )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
include_directories (
                                     ../
                                    )
set (HDR  
         state_transition_unit.h
         cmd_state_unit.h
         events_state_traits.h
    )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

