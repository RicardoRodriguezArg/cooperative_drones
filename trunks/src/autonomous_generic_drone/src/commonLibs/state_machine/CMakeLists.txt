project ( state_machine )
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(
                                    ../
                                    ../tinyxml2
                                    ../netlink
                                    ../builders

                                )
set ( HDRS generic_state_machine.h

                    #    state_create_builder.h
		
)
add_executable(${PROJECT_NAME} main.cpp
                            ${HDRS}
                            )
