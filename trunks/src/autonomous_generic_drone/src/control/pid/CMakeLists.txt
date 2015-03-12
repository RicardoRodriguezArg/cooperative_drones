project(control)
cmake_minimum_required(VERSION 2.8)



ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)

set (HDR 
                control_definitions.h
                control_pid.h
        )
set (SRC main.cpp)
add_executable(${PROJECT_NAME} ${SRC}
                            ${HDR}
                            )
#target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

