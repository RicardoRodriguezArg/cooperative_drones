#ifndef INTERFACEFRAMER_H
#define INTERFACEFRAMER_H
namespace COMUNICACION
{
class IFramer
{
public:
    virtual ~IFramer(){}
    virtual int frame(char *,const int & ) =0;
    virtual int unFrame(char * ) =0 ;
    virtual char * getFrameData() const = 0;
    virtual void crearFrameBuffer()=0;
    virtual int getSize() const=0;
    virtual  char * getFrameBuffer() const = 0;

};
}
#endif // INTERFACEFRAMER_H
