/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-04-2015
  *@brief:
  *
  */
#ifndef FRAMERCOMUNICACION_H
#define FRAMERCOMUNICACION_H
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "interfaceframer.h"

namespace COMUNICACION {


static const int aSizeTypeDefault=4;
static const int gDefaultMAxSizeType=10;

///================================
template<class Entrada, int  BufferSize = 512>
class GenericFramer : public IFramer

{
public:

    GenericFramer(Entrada * const aSerializeCmd = nullptr,const int & aSizeType = aSizeTypeDefault):sizeFrame(aSizeTypeDefault)
      //, frameBuffer(0)
      ,mSerializeCmd(aSerializeCmd)
      ,frameBuffer(nullptr)

    {
        //creacion del buffer
        createFrameBuffer(BufferSize);
    }

    ~GenericFramer()
    {
        //chequeo que tenga ese metodo
        if (mSerializeCmd ) mSerializeCmd->size();
         if (frameBuffer) {
             delete frameBuffer;
             frameBuffer=nullptr;
         }
    }
    void setSize(const int & aSize=aSizeTypeDefault)
    {
        if (aSize<0) return;
        if (aSize>10) return;
        sizeFrame=aSize;
    }
    int getSize() const
    {
        return static_cast<int>(sizeFrame);
    }
    void setFrameData(Entrada * aCmmd =0 )
    {
        mSerializeCmd=aCmmd;
    }
    char * getFrameBuffer() const
    {
        return frameBuffer;
    }
    int frame(char * aBuffer = 0,const int & aSizeType = aSizeTypeDefault)
    {
        if (aSizeType<=0) return -1;//parametro invalido
        if(!aBuffer) return -2; //buffer vacio
        if (!frameBuffer) {
             frameBuffer= new char[BufferSize];
        }
      //  std::cout<<"sizeof(*aBuffer)-->"<<sizeof(*aBuffer)<<std::endl;

        //if (sizeof(*aBuffer)==0) return -3;
        memcpy(frameBuffer,&aSizeType, sizeof (aSizeType));
        memcpy(frameBuffer +  sizeof (aSizeType), aBuffer, aSizeType );
        sizeFrame=aSizeType +  sizeof (aSizeType);
        return 0;
    }

    int unFrame(char * aBuffer= 0)
    {
        if (!aBuffer) return 0;
        if (!frameBuffer) {
             frameBuffer= new char[BufferSize];
        }
        sizeFrame=0;
        memcpy(&sizeFrame, aBuffer, sizeof (sizeFrame));
        if ((sizeFrame + sizeof (sizeFrame))>=BufferSize ) return -2;
        memcpy(frameBuffer , aBuffer+ sizeof (sizeFrame), sizeFrame);
        return 0;
    }
    char * getFrameData() const
    {
        return this->frameBuffer;
    }
    void crearFrameBuffer()
    {
        if (!frameBuffer)     createFrameBuffer(BufferSize);
    }
private:
    GenericFramer(const GenericFramer &){}

    int createFrameBuffer(const int & aSizeType = aSizeTypeDefault)
    {
        if (sizeFrame==-1) return -1;
        if(aSizeType==0) return -2;

        frameBuffer= new char[BufferSize];
        return 0;
    }

    u_int32_t sizeFrame;
    Entrada * mSerializeCmd;
    char  * frameBuffer ;

} ;





}//fin namespace
#endif // FRAMERCOMUNICACION_H
