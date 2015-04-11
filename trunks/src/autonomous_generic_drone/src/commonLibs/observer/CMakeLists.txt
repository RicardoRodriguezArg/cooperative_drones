project( observer )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(CMAKE_BUILD_TYPE Debug)

set ( SRCHDR
            observer.h
            sujeto.h

    )
set ( SRCIMP
          main.cpp


    )



add_library (${PROJECT_NAME} ${SRCHDR} ${SRCIMP} )
target_link_libraries( ${PROJECT_NAME} 

			)
