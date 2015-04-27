#ifndef ITSERIALIZADOR_H
#define ITSERIALIZADOR_H
namespace NSMensaje {

class ISerializer
{
public:
    virtual ~ISerializer(){}
    virtual void limpiarSerializador(int &) =0 ;
    virtual void cerrarSerealizador(int &) = 0;

};
}
#endif // ITSERIALIZADOR_H

