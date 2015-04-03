project (factory)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../)
set (HDRS base_class.h
                    generic_factory.h
                    factory_register.h)
add_executable(${PROJECT_NAME} main.cpp
                            ${HDRS}
                            )
