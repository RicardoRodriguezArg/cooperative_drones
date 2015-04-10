/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief:
  *
  */
#ifndef PROXY_BASE_H
#define PROXY_BASE_H
#include <string>
#include <mutex>
#include <unordered_map>
#include <vector>
#include "definitions.h"
namespace NSProxy {
template< class Serializer,
          , class CommInterface
          , class ProxyProcessInterface
          , class SubCmd
          , class IServiceInterface
        >
class ProxyBase : public IServiceInterface
{
    protected:
    ProxyBase(const unsigned & aProxyID):MsgSenderPtr(nullptr)
      ,PROXYID(aProxyID)

    {}
    ~ProxyBase(){}
    void setConnector(const std::string & SenderIDChannel ,CommInterface * const aMsgSender)
    {
        ConnectorMaps.insert(std::make_pair(SenderIDChannel,aMsgSender));
    }
    void setProxyProccess(const std::string & aProxyProcessID, ProxyProcessInterface * const aProxyProcess)
    {
        ProxyProxyMap.insert(std::make_pair(aProxyProcessID,aProxyProcess));
    }

    void setDataTypeSerializer(const std::string & aSerializerID, Serializer * const aSerializer )
    {
      MsgSerializerMap.insert(std::make_pair( aSerializerID,aSerializer));
    }

    void initConnector(const std::string & aConnectorTypeId)
    {
        const auto iterator=ConnectorMaps.find(aConnectorTypeId);
        if(iterator!=ConnectorMaps.end())
        {
                (iterator->second)->inicializarCliente(ErrorCode);
        }
    }
    void setCmdVectorID(const unsigned & aCmdId )
    {
       CmdIdVector.emplace_back(aCmdId );
    }
    bool isCmdExecutable(const unsigned & aCmdId)
    {

    }
    virtual void execute( SubCmd aCmd, int &)
    {

    }
    virtual  SubCmd  * geSubCmd(const std::string &) const
    {}

    std::unordered_map<std::string,Serializer * const> MsgSerializerMap;
    std::string Buffer;
    CommInterface * const MsgSenderPtr;
    std::mutex mutex;
    std::unordered_map<std::string, CommInterface * const> ConnectorMaps;
    std::unordered_map<std::string, ProxyProcessInterface * const> ProxyProxyMap;
    std::vector<unsigned> CmdIdVector;
    const unsigned PROXYID;
    int ErrorCode;

};
}
#endif // PROXY_BASE_H
