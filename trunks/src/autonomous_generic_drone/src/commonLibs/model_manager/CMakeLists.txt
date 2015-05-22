project( model_manager )
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


#------------------------------------------
include_directories(
                    ../
                    )
set ( SRCHDR
            modelmanager.h
            imodel_properties.h
            model_property_unit.h
         
    )



add_executable( testmodelo main.cpp ${SRCHDR})
target_link_libraries( testmodelo

                        )


