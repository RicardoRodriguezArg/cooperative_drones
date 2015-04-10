project( tests )
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
find_package(Threads REQUIRED)

include (/home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/src/commonLibs/cmake/FindGMock.cmake)
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

include_directories (
                        ../

                        /usr/local/lib
                        ${GTEST_INCLUDE_DIRS}
                        ${GMOCK_INCLUDE_DIRS}
                    )
set (HDR  

    )

set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_link_libraries(${PROJECT_NAME}
                                    -lpthread

                                    ${GTEST_LIBRARIES}
                                    ${GMOCK_BOTH_LIBRARIES}
                                    ${CMAKE_THREAD_LIBS_INIT}
)
