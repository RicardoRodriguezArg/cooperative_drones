#include "builders_streams.h"
#include "builder_options.h"
#include "../utils_generics/xml_reader.h"
#include "builders_proxy.h"
#include "../proxy_base/proxy_base.h"
#include "../factory/base_class.h"
namespace {
  namespace Test
  {
    struct Proxy:public KERNEL::FactoryBase
    {
      Proxy()
      {
       }
      void setProxyId(const unsigned & aProxyID)
      {}
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
  NSBuilders::Builders<NSCommonsLibs::BuilderType::ProxyType,NSBuilders::StreamBuilderType,::Test::Proxy> aProxyBuilder(&aStreamBuilder);
  aProxyBuilder.buildAll(aErrorCode);



  return 0;
}
