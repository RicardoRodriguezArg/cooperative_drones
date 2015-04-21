project(Reactor)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
find_package( Threads )

include (../cmake/findGlog.cmake)
include_directories(${GLOG_INCLUDE_DIR})
set (HDR reactor.h
         
    )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
target_link_libraries( ${PROJECT_NAME}
                        ${CMAKE_THREAD_LIBS_INIT}
                         ${GLOG_LIBRARY}
                       )
