project( utils_generics )
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set (HDR generis_strutures.h
	 generics_multi_maps.h
         linux_uitls.h
         xml_reader.h
         utils_transform_data.h
         
    )
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
#add_executable(test_error test_tm.cpp ${HDR})
