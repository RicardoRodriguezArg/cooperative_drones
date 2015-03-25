project( comunicacion )
cmake_minimum_required(VERSION 2.6)
set(CMAKE_BUILD_TYPE Debug)
find_package( Threads )
#inclusion de la libreria de mensajes para probar este patron


include_directories (
                    ../

                     ../netlink
                  
                    )
link_directories (

                  
                 )




set ( SRCHDR
                framercomunicacion.h
                icomm.h
                tcpcommunication.h
                UDPComm.h
                interfaceframer.h

    )
set ( SRCIMP
                        main.cpp


    )


add_library (${PROJECT_NAME} ${SRCHDR} ${SRCIMP} )
target_link_libraries( ${PROJECT_NAME}
                            ${CMAKE_THREAD_LIBS_INIT}

                        )

