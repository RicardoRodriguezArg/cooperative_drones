cmake_minimum_required(VERSION 2.6)
project( netLink )


set(CMAKE_BUILD_TYPE Debug)

aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})
add_library(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries( ${PROJECT_NAME}
                       ${PROTOBUF_LIBRARY}
                    )
