/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief:
  *
  */
#ifndef TCPCOMMUNICATION_H
#define TCPCOMMUNICATION_H
#include "icomm.h"
#include "framercomunicacion.h"
#include "../netlink/socket.h"
#include <cstdlib>


namespace COMUNICACION {
#define BUFFERSIZE 1024
#define CONFIGURATOR_PTR_NULL 0
static int gDefaultIntValue=-1;
template<typename MsgType>
class TCPCOMM: public IComm
{
public:
    explicit TCPCOMM():mCliente(nullptr)


      ,mServer(nullptr)

      ,mErrorFrameOperation(-1)
      ,mDestino(std::string("localhost"))
      ,mPuerto(std::string("5000"))
      ,mBloqueante(false)
       ,mBufferSize(512)
      ,mComunicationError(-1)
    {

        mFramerGenerico.crearFrameBuffer();
    }
    ~TCPCOMM()
     {

        cerrarComunicacion();
        if(mCliente)
        {
               delete mCliente;
                mCliente=nullptr;
        }
        if (mServer!=nullptr){

            delete mServer;
            mServer=nullptr;
        }

     }

    int inicializarcomunicacion()
    {
    return 0;
    }
    void setLocalPort(const std::string &)
    {

    }
    void leer(MsgType & aMsgData , int & aError)
    {
        if (!mCliente) {
            aError=-100;// el cliente no esta inicializado
            return;
        }
        try
        {
            aMsgData.clear();
            char buffer[BUFFERSIZE];
            mComunicationError=static_cast<volatile int>(mCliente->read(buffer,BUFFERSIZE));
            if(mComunicationError>0)
            {
              aError=mFramerGenerico.unFrame(buffer);
              if (aError!=0) return;//error en la recepcion del byte de comunicacion
              std::string aBuffer(mFramerGenerico.getFrameBuffer(),mFramerGenerico.getSize());
              aMsgData=aBuffer;
              aError=0;//ERROR_SERVER_LECTURA_OK;

            }
             else
           {
               aError=-7;//ERROR_SERVER_COMUNICATION_CLOSED;
            }

        }
        catch(...)
        {
             aError=-8;//ERROR_SERVER_COMUNICATION_FAIL;
             return;
        }
    }
    void escribir(MsgType * const aPtrDataMsg, int & aError)
    {
        if (!aPtrDataMsg)
        {
          return ;//TODO: Homogeneizar los codigos de errores
        }
        if(mCliente==nullptr)
        {
            aError=-3;
            return;
        }
        try{
            mErrorFrameOperation=mFramerGenerico.frame(const_cast<char *>( aPtrDataMsg->c_str()),
                                               aPtrDataMsg->size());
            if(mErrorFrameOperation!=0)
            {
                aError=mErrorFrameOperation;
                return ;
            }
            this->mCliente->send(mFramerGenerico.getFrameBuffer(),mFramerGenerico.getSize());
            aError= 0;
        }
        catch(...)
        {
            aError=-1;
        }
    }
    int setPort(const std::string &  aPort)
    {
        mPuerto=aPort;
    }
    std::string getPort(void) const
    {
        return mPuerto;
    }
    int setDestino(const std::string & aDestino)
    {
        mDestino=aDestino;
    }
    std::string getDestino() const
    {}

    int cerrarComunicacion()
    {
        if (mServer) mServer->disconnect();
        if (mCliente) mCliente->disconnect();
    }
    int setBufferSize(const int & )
    {}
    int getBufferSize() const
    {}
    void reConnectServer(int & aErrorCode)
    {
        try
        {

        }
        catch(...)
        {}
    }
    void inicializarServer(int & aError=gDefaultIntValue) noexcept(true)
    {

        try{
        mServer= new NL::Socket(atoi(mPuerto.c_str()));
        mCliente=mServer->accept();
        aError= 0;//ERROR_SERVER_SOCKET_INICIALIZADO;

        }
        catch(...)
        {
            aError= -2;//ERROR_SERVER_SOCKET_NO_INICIALIZADO;
        }
    }
    void inicializarCliente(int & aError=gDefaultIntValue) noexcept(true)
    {
        if(mCliente!=nullptr)
        {
            delete mCliente;
            mCliente=nullptr;
        }
        try{
             mCliente= new NL::Socket(mDestino,atoi(mPuerto.c_str()));
             aError= 0;//ERROR_SERVER_SOCKET_INICIALIZADO;
        }
        catch(...)
        {
            aError= -2;//ERROR_SERVER_SOCKET_NO_INICIALIZADO;
        }
    }
    void setBlockingConnection(const bool & aBool)
    {
        if(mServer!=nullptr) mServer->blocking(aBool);
        if(mCliente!=nullptr) mCliente->blocking(aBool);
    }
private:

    TCPCOMM( const TCPCOMM &);
    const TCPCOMM & operator=(const TCPCOMM &);

    NL::Socket * mCliente;

    COMUNICACION::GenericFramer<std::string> mFramerGenerico;
    NL::Socket * mServer;
    int mErrorFrameOperation;
    std::string mDestino;
    std::string mPuerto;
    bool mBloqueante;

    const int mBufferSize;
    volatile int mComunicationError;
};
}
#endif // TCPCOMMUNICATION_H
