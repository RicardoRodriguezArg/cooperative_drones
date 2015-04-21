project( builders)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

find_package( Threads )

include (../cmake/findGlog.cmake)

set(destDir  ${CMAKE_CURRENT_SOURCE_DIR}/../../ref/config)
file (GLOB  CONFIG_XML_FILES
                                            ${CMAKE_CURRENT_SOURCE_DIR}../../ref/config/*.xml

        )
set ( XML_FILES
			../../../config/config/kernel_configuration_option.xml
			#../../../config/config/generaloptionconfig.xml



      )
file (MAKE_DIRECTORY  ${CMAKE_BINARY_DIR}/ref/config  )
set ( output_directory ${CMAKE_BINARY_DIR}/ref/config )
file (COPY ${XML_FILES} DESTINATION ${output_directory} )

include_directories(
                                     ../
                                    ../tinyxml2
                                    ../netlink
                                    ${GLOG_INCLUDE_DIR}

                                    )
set (HDR builders_traits.h
                builders_streams.h
                builder_options.h
                builders_proxy.h
                utils_builder.h
                builder_proxy_info.h
         
    )
set (SRC
                ../tinyxml2/tinyxml2.cpp
                ../netlink/socket.cc
                ../factory/generic_factory.cpp
                main.cpp
        )

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

add_executable(test_builders_proxy test_builders_proxy.cpp
                                                            ../factory/generic_factory.cpp
                                                            ../tinyxml2/tinyxml2.cpp
                                                            ../netlink/socket.cc
                                                            ${HDR}
                )

target_link_libraries( ${PROJECT_NAME}
                        ${CMAKE_THREAD_LIBS_INIT}
                         ${GLOG_LIBRARY}
                       )
target_link_libraries( test_builders_proxy
                        ${CMAKE_THREAD_LIBS_INIT}
                         ${GLOG_LIBRARY}
                       )
