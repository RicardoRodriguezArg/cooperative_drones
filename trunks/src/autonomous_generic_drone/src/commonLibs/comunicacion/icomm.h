/**
 *
 * Copyright (c) 2013 Invap S.E. Ltd.
 * All rights reserved.
 *
 * @file   icomm.h
 * @Author Rodriguez, Alberto Ricardo
 * @date   10/10/2013
 * @brief  Define interface de comunicacion, la cual implementaran las diferentes especializaciones
 */

#ifndef ICOMM_H
#define ICOMM_H
#include <string>

namespace COMUNICACION {

class IComm{
public:
        virtual ~IComm(){}
        virtual int inicializarcomunicacion() = 0;
        virtual int cerrarComunicacion() = 0;
        virtual int setBufferSize(const int & )=0;
        virtual int getBufferSize() const = 0;
        virtual void inicializarServer(int &) =0;
        virtual void inicializarCliente(int &)= 0;
        virtual int setPort(const std::string &  aPort) = 0;
        virtual std::string getPort(void) const = 0;
        virtual int setDestino(const std::string &)=0;
        virtual std::string getDestino() const = 0;
};
}
#endif // ICOMM_H
