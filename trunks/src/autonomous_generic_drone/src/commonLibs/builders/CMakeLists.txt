project( builders)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")


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

include_directories (
                                     ../
                                    ../tinyxml2
                                    ../netlink

                                    )
set (HDR builders_traits.h
                builders_streams.h
                builder_options.h
         
    )
set (SRC
                ../tinyxml2/tinyxml2.cpp
                ../netlink/socket.cc
                main.cpp
        )

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
