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
namespace Proxy {
template< class Serializer
                    , class CommInterface
                    ,class ProxyProcessInterface
                    ,class MetaCmd
                    , class IServiceInterface
                >
class ProxyBase : public IServiceInterface
{
    protected:
    ProxyBase(Serializer * const aSerializer,const unsigned & aProxyID):MsgSerializer(aSerializer)
      ,MsgSenderPtr(nullptr)
      ,PROXYID(aProxyID)

    {}
    void setConnector(const std::string & SenderIDChannel ,CommInterface * const aMsgSender)
    {
        ConnectorMaps.insert(std::make_pair(SenderIDChannel,aMsgSender));
    }
    void setProcessProccess(const std::string & aProxyProcessID, ProxyProcessInterface * const aProxyProcess)
    {
        ProxyProxyMap.insert(std::make_pair(aProxyProcessID,aProxyProcess));
    }
    void initConnector(const std::string & aConnectorTypeId)
    {
        const auto iterator=ConnectorMaps.find(aConnectorTypeId);
        if(iterator!=ConnectorMaps.end())
        {
                (iterator->second)->init();
        }
    }
    void setCmdVectorID(const unsigned & aCmdId )
    {
            CmdIdVector.emplace_back(aCmdId );
    }
    bool isCmdExecutable(const unsigned & aCmdId)
    {

    }
    virtual void execute( MetaCmd aCmd, int &)
    {

    }
    virtual  MetaCmd  * getMetaCmd(const std::string &) const
    {}

    Serializer * const MsgSerializer;
    std::string Buffer;
    CommInterface * const MsgSenderPtr;
    std::mutex mutex;
    std::unordered_map<std::string, CommInterface * const> ConnectorMaps;
    std::unordered_map<std::string, ProxyProcessInterface * const> ProxyProxyMap;
    std::vector<unsigned> CmdIdVector;
    const unsigned PROXYID;

};
}
#endif // PROXY_BASE_H
