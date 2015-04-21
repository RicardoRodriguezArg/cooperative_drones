project (factory)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../
                    )

find_package( Threads )

include (../cmake/findGlog.cmake)

include_directories(${GLOG_INCLUDE_DIR})

set (HDRS base_class.h
                    generic_factory.cpp
                    factory_register.h
      )

add_executable( ${PROJECT_NAME} main.cpp
                            ${HDRS}
                            )

target_link_libraries( ${PROJECT_NAME}
                        ${CMAKE_THREAD_LIBS_INIT}
                         ${GLOG_LIBRARY}
                       )
