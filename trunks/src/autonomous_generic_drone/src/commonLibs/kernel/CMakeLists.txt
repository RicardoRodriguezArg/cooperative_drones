project( kernel )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
include_directories (
                                     ../
                                    ../state_machine
                                  )
set (HDR 

                kernel.h
                i_kernel_interface.h
    )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
#add_executable(test_error test_tm.cpp ${HDR})
