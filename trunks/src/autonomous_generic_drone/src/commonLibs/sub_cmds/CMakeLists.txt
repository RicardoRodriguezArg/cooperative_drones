project( sub_cmds )
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

set ( SRCHDR
                sub_cmds.h
                sub_command_interface.h
   )
set ( SRCIMP
          main.cpp
    )

add_library (${PROJECT_NAME} ${SRCHDR} ${SRCIMP} )
target_link_libraries( ${PROJECT_NAME} 

			)
