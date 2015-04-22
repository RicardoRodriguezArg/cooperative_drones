project ( state_machine )
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include( ../../commonLibs/cmake/findGlog.cmake)
include_directories(
                                ../
                                ${GLOG_INCLUDE_DIR}
                                ../../commonLibs
                                ../../commonLibs/tinyxml2
                                ../../commonLibs/netlink
                                ../../commonLibs/utils_generics
                                ../../commonLibs/state_machine
                                ../../commonLibs/factory
                                ../../commonLibs/Reactor
                                ../servers_service
                                ../cmd_processor

                                )




set ( HDRS 
                    ../../commonLibs/tinyxml2/tinyxml2.cpp
                    ../../commonLibs/netlink/socket.cc
                   #     ../../commonsLibs/netlink/socket.cc
                        ../../commonLibs/factory/generic_factory.cpp
                        ../../commonLibs/factory/factory_register.h
                        ../servers_service/servers_manager.h
                        state_create_builder.h
                        state_configurate_component.h
                        create_kernel_components.h
		
)
add_executable(${PROJECT_NAME} main.cpp
                            ${HDRS}
                            )
target_link_libraries( ${PROJECT_NAME}
                        ${GLOG_LIBRARY}
                        ${CMAKE_THREAD_LIBS_INIT}

                       )
