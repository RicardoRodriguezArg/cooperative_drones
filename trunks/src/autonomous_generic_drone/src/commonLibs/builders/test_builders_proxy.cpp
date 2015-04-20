#include "builders_streams.h"
#include "builder_options.h"
#include "../utils_generics/xml_reader.h"
#include "builders_proxy.h"
#include "../proxy_base/proxy_base.h"
#include "../factory/base_class.h"
namespace {
  namespace Test
  {
    struct SerializerInterface
    {};
    struct NanoSerializer : public SerializerInterface
    {};
    struct ProtoSerializer : public SerializerInterface
    {};
    struct ComInterface
    {

    };
    struct Proxy:public KERNEL::FactoryBase
    {
      Proxy()
      {
       }
      void setProxyId(const unsigned & aProxyId)

      {}
      void setConnector(const std::string & SenderIDChannel ,COMUNICACION::IComm * const aMsgSender)
      {

      }
      void setDataTypeSerializer(const std::string & aMsgChannel, SerializerInterface * const aSerializer )
      {

      }

      static const int TEST_PROXY_ID_DEFAULT=100;
      virtual int getID()
      {
        return TEST_PROXY_ID_DEFAULT;
      }
    };
    struct StreamBuilder{
      std::unordered_map<key,COMUNICACION::IComm * const,std::hash<key>> getComMapOption()
      {
         return comm_map;
      }
      std::unordered_map<key,COMUNICACION::IComm * const,std::hash<key>> comm_map;
    };
  }
}
int main()
{
  ::Test::StreamBuilder aStreamBuilderTest;
  ::Test::Proxy aProxy;
  int aErrorCode=-1;
  NSBuilders::StreamBuilderType aStreamBuilder("/home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/config/config/generaloptionconfig.xml");
  aStreamBuilder.buildAll(aErrorCode);
  /*
  std::unordered_map<std::string,::Test::Proxy * ,std::hash<std::string>> ProxyPtrContainner;
  ::Test::Proxy * aPtr=nullptr;
  ProxyPtrContainner.insert(std::make_pair("puntero_nulo",aPtr));
  */

  NSBuilders::Builders<NSCommonsLibs::BuilderType::ProxyType,NSBuilders::StreamBuilderType,::Test::Proxy
      ,::Test::SerializerInterface,::Test::ProtoSerializer,::Test::NanoSerializer> aProxyBuilder(&aStreamBuilder);

  aErrorCode=-1;
  aProxyBuilder.buildAll(aErrorCode);
  std::cout<<"ErrorCode; "<<aErrorCode<<std::endl;


  return 0;
}
