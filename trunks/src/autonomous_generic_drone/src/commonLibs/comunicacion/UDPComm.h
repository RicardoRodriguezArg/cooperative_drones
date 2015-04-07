/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief:
  *
  */
#ifndef UDPCOMM_H
#define UDPCOMM_H
#include <cstdlib>
#include "icomm.h"
#include "framercomunicacion.h"
#include "../netlink/socket.h"
#include "../utils_generics/utils_transform_data.h"



namespace{
static const int gDefaultBufferSize=512;
static const unsigned gDefaultRemotePort=5001;
static const std::string gDefaultRemoteIp= std::string("localhost");
static int gDefaultIntErrorValue=-1;
}
namespace COMUNICACION {
template<typename MsgType>
class UDPComm: public IComm {
public:
   explicit UDPComm( const std::string & aRemoteIp = gDefaultRemoteIp
            , const unsigned & aRemotePort = gDefaultRemotePort ):mCliente(nullptr)
      ,mServer(nullptr)

      ,mBufferSize(gDefaultBufferSize)
      ,mErrorFrameOperation(-1)
      ,mPuerto(std::move("5001"))
      ,mDestino(aRemoteIp)
      ,mBloqueante(false)
      ,mComunicationError(-1)
      ,localPort(5000)
      ,remotePort(aRemotePort)
      ,mBuffer(nullptr)

    {

        mFramerGenerico.crearFrameBuffer();

    }

    ~UDPComm()
    {
        cerrarComunicacion();

       if(mBuffer!=nullptr)
         {
           delete [] mBuffer;
           mBuffer=nullptr;
        }
    }
    void setRemoteIp(const std::string & aRemoteIp)
    {
        mDestino=aRemoteIp;
    }
    void setRemotePort(const unsigned & aRemotePort )
    {
        remotePort=aRemotePort;
    }
    void inicializarServer(int & aErrorCode) noexcept(true)
    {
        aErrorCode=-1;
        try{

            mServer=  new NL::Socket(mDestino,remotePort,remotePort);
            mServer->blocking(false);
            aErrorCode=0;
        }
        catch(...)
        {

            aErrorCode=-2;
        }


        if(aErrorCode==0) {

            mBuffer=new char[mBufferSize];
        }
    }
    unsigned getRemotePort()
    {

        return remotePort;
    }
    
    
    void inicializarCliente(int & aErrorCode) noexcept(true)
    {
        aErrorCode=-1;
       // if(!validateIpAddress(mDestino)) return;
        try {
            mCliente=new NL::Socket(mDestino,remotePort,localPort);
            mCliente->blocking(false);
            aErrorCode=0;

        }
        catch(...)
        {
                aErrorCode=-2;

        }

    }

     int cerrarComunicacion()
    {
         if (mServer!=nullptr) {
             mServer->disconnect();
             delete mServer;
             mServer=nullptr;
         }
         if (mCliente!=nullptr){

             mCliente->disconnect();
             delete mCliente;
             mCliente=nullptr;
         }
        return 0;
    }
    int setBufferSize(const int & )
    {
        return -1000;
    }
    int getBufferSize() const
    {
        return -1000;
    }
    int setPort(const std::string &  aPort)
    {
        return -1000;
    }
   std::string getPort(void) const
   {
       return mPuerto;
   }
   int setDestino(const std::string &)
   {
       return -1000;
   }
   std::string getDestino() const
   {
       return mDestino;
   }


   int inicializarcomunicacion()
   {
       return -1000;
   }
   //=================================================
   void leer( MsgType & aMsg, int & aErrorCode)
   {
        aErrorCode=-3;
        if(!mBuffer) return;
       aErrorCode=-2;
       if(!mServer) return;
       mBuffer[mBufferSize-1]='\0';
       try
        {
         aErrorCode=mServer->readFrom(mBuffer,mBufferSize,&mDestino,&remotePort);
         if(aErrorCode!=-1)
         {
            mErrorFrameOperation=mFramerGenerico.unFrame(mBuffer);
            if(mErrorFrameOperation==0)
            {
              mBufferString.assign(mFramerGenerico.getFrameBuffer(),mFramerGenerico.getSize());
              aMsg=mBufferString;
              aErrorCode=0;
            }
         }
       }
       catch(...)
       {
           aErrorCode=-4;
       }
   }
   //=================================================
   void escribir(MsgType  * const  aMsg, int & aErrorCode )
   {
       aErrorCode=-1;
       if(!aMsg){

           return;
       }
       if(!mCliente)
       {
           aErrorCode=-3;
           return;
       }
       try
       {
           mErrorFrameOperation=mFramerGenerico.frame(const_cast<char *>( aMsg->c_str()),
                                               aMsg->size());
            if(mErrorFrameOperation!=0)
           {
               aErrorCode=mErrorFrameOperation;
               return ;
           }
            mCliente->sendTo(mFramerGenerico.getFrameBuffer(),mFramerGenerico.getSize(), mDestino, remotePort);
            aErrorCode=0;
       }
       catch(...)
       {
           aErrorCode=-3;
       }


   }
   void setLocalPort(const unsigned & aLocalPort)
   {
        localPort=aLocalPort;
   }
   void setLocalPort(const std::string & aLocalPort)
   {
     NSUtils::getValueFromString<unsigned>(localPort,aLocalPort);

   }
   void setFramerPaquetes( COMUNICACION::IFramer * const aFramerPtr = nullptr) noexcept(true)
   {
       if(mFramerGenerico)
       {
           delete mFramerGenerico;
           mFramerGenerico=nullptr;
       }
       mFramerGenerico=aFramerPtr;
       mFramerGenerico.crearFrameBuffer();
   }
private:

   bool validateIpAddress(std::string &ipAddress)
   {
       if(ipAddress.compare("localhost")==0) ipAddress.assign("127.0.0.1");
       struct sockaddr_in sa;
       int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));

       return result != 0;
   }

    NL::Socket * mCliente;
    NL::Socket * mServer;
    const int mBufferSize;
    int mErrorFrameOperation;
    std::string mPuerto;
    std::string mDestino;
    bool mBloqueante;
   volatile int mComunicationError;
    unsigned localPort;
    COMUNICACION::GenericFramer<std::string> mFramerGenerico;
    unsigned remotePort;
    char * mBuffer;
    std::string mBufferString;



};
}
#endif // UDPCOMM_H
