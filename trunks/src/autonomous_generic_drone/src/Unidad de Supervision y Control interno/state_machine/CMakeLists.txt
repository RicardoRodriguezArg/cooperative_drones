project ( state_machine )
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
                                    ../
                                    ../../commonLibs
                                    ../../commonLibs/tinyxml2
                                    ../../commonLibs/netlink
                                   ../../commonsLibs/utils_generics
                                ../../commonsLibs/state_machine
                                ../servers_service
                                ../cmd_processor

                                )




set ( HDRS 

                      ../../commonLibs/tinyxml2/tinyxml2.cpp
                    ../../commonLibs/netlink/socket.cc
                   #     ../../commonsLibs/netlink/socket.cc
                        state_create_builder.h
                        state_configurate_component.h
		
)
add_executable(${PROJECT_NAME} main.cpp
                            ${HDRS}
                            )
