project( utils_generics )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set (HDR generis_strutures.h
	 generics_multi_maps.h
         
    )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
