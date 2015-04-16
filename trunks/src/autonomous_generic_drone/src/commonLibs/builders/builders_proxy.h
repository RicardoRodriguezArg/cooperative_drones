#ifndef BUILDERS_PROXY_H
#define BUILDERS_PROXY_H
#include "builders_traits.h"
#include "utils_builder.h"
#include "builder_proxy_info.h"
#include "../factory/factory_register.h"
namespace NSBuilders
{
  namespace{
    constexpr int ERROR_CODE_INDEX=1;
  }
  /**
   *@brief: Esta clase no realiza el parsing del archivo XML sino que toma la clase que encapsula las opciones de
   *otro builder (En este caso de comunicaciones)
   */
  template<class StreamBuilder,class Proxy,class ...Args>
  class Builders<NSCommonsLibs::BuilderType::ProxyType,StreamBuilder,Proxy,Args...> : public IBuilderInterface
  {
    typedef NSBuilders::Utils::ProxyData<Proxy> ProxyDataConfig;
  public:
    Builders(StreamBuilder * const aStreamBuilder=nullptr):StreamBuilderPtr(aStreamBuilder)
    {}
    /**
     * @brief buildAll toma el puntero a la estructura que contienen las opciones del builder que realizo el parsing de las opciones de comunicacion
     * @param aErrorCode codigo de error del builder
     */
    void buildAll(int & aErrorCode)
    {
      aErrorCode=std::get<NSCommonsLibs::ERROR_CODES::ERROR_CODE_INDEX>(NSCommonsLibs::ERROR_CODES::BUILDER_PROXY_ERROR);
      if(StreamBuilderPtr!=nullptr)
        {
           createProxyMap();//extraigo los nombre sin repeticiones
           registerProxyInFactory();
           printProxysNames();
        }

    }

  private:
    void createProxyMap()
    {
      const auto com_map=std::move(StreamBuilderPtr->getComMapOption());
      for(auto iterator=com_map.begin();iterator!=com_map.end();iterator++)
        {
          if(!(iterator->first).ProxyDescription.empty()){
             ProxyDataConfig_.clear();
             const auto result=ProxyPtrContainner.insert(std::make_pair((iterator->first).ProxyDescription,ProxyDataConfig_));
             if(result.second)
             {
             ProxyPtrContainner[(iterator->first).ProxyDescription].ProxyID=(iterator->first).ProxyID;
             std::cout<<"ProxyId(ProxyPtr): "<<ProxyPtrContainner[(iterator->first).ProxyDescription].ProxyID<<std::endl;
             ProxyPtrContainner[(iterator->first).ProxyDescription].DataType=(iterator->first).data_type;/*Command Data Event*/
             ProxyPtrContainner[(iterator->first).ProxyDescription].MsgDataType=(iterator->first).MsgType;
            }
            }
        }
    }
    void printProxysNames()
    {
      for(auto iterator= ProxyPtrContainner.begin();iterator!=ProxyPtrContainner.end();iterator++)
        {
          std::cout<<"ProxyName: "<<iterator->first<<std::endl;
        }
    }
    void registerProxyInFactory()
    {
      for(auto iterator= ProxyPtrContainner.begin();iterator!=ProxyPtrContainner.end();iterator++)
        {
            KERNEL::KernelFactory::getInstance().registerFactoryFunction((iterator->first),[](void)->KERNEL::FactoryBase *{return new Proxy();});
            //actaulizo el puntero del mapa
            (iterator->second).ProxyPtr=reinterpret_cast<Proxy *>(KERNEL::KernelFactory::getInstance().createInstance((iterator->first)).get());
            //aca configuramos al proxy
        }
    }
    void configProxys()
    {

    }
    ProxyDataConfig ProxyDataConfig_;
    std::unordered_map<std::string,ProxyDataConfig ,std::hash<std::string>> ProxyPtrContainner;
    StreamBuilder * const StreamBuilderPtr;

  };
}
#endif // BUILDERS_PROXY_H
