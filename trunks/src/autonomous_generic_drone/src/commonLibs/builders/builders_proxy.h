#ifndef BUILDERS_PROXY_H
#define BUILDERS_PROXY_H
#include "builders_traits.h"
#include "utils_builder.h"
#include "builder_proxy_info.h"
#include "../factory/factory_register.h"
#include "../utils_generics/utils_transform_data.h"
#include "definitions.h"

namespace NSBuilders
{
  namespace{
    constexpr int ERROR_CODE_INDEX=1;
  }
  /**
   *@brief: Esta clase no realiza el parsing del archivo XML sino que toma la clase que encapsula las opciones de
   *otro builder (En este caso de comunicaciones)
   */
  template<class StreamBuilder,class Proxy,class SerializadorInterface,class ProtoSerializer,class NanoSerializer, class ...Args>
  class Builders<NSCommonsLibs::BuilderType::ProxyType,StreamBuilder,Proxy,SerializadorInterface,ProtoSerializer,NanoSerializer,Args...> : public IBuilderInterface
  {
    typedef NSBuilders::Utils::ProxyData<Proxy> ProxyDataConfig;
    const std::string PROXY_OUT_STREAM=std::move(std::string("out"));
  public:
    Builders(StreamBuilder * const aStreamBuilder=nullptr):StreamBuilderPtr(aStreamBuilder)
    ,ProxyId(std::get<NSCommonsLibs::ERROR_CODES::ERROR_CODE_INDEX>(NSCommonsLibs::ERROR_CODES::OK_ERROR_TUPLE))
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
            configProxys((iterator->first),&(iterator->second));
        }
    }
    void configProxys(const std::string & aProxyDescription,ProxyDataConfig * const aProxyDataConfigPtr )
    {
      //seteo del id del proxy
      NSUtils::getValueFromString<int>(ProxyId,aProxyDataConfigPtr->ProxyID);
      (aProxyDataConfigPtr->ProxyPtr)->setProxyId(static_cast<unsigned>(ProxyId));
      const auto aComPtr=StreamBuilderPtr->getComInterface(aProxyDescription,PROXY_OUT_STREAM,aProxyDataConfigPtr->DataType);
      if( aComPtr!=nullptr)
        {
          (aProxyDataConfigPtr->ProxyPtr)->setConnector(aProxyDataConfigPtr->DataType,aComPtr);
          (aProxyDataConfigPtr->ProxyPtr)->setDataTypeSerializer(aProxyDataConfigPtr->DataType,getSerializer(aProxyDataConfigPtr->MsgDataType));
        }

    }

    SerializadorInterface * getSerializer(const std::string & aSerializerType)
    {
    SerializadorInterface * aPtr=nullptr;
      if(aSerializerType.compare("proto")==0) aPtr=(new ProtoSerializer);
      //TODO: Falta crear el serializador de comandos Nano
      if(aSerializerType.compare("nano")==0) aPtr=(new NanoSerializer);
      return aPtr;
    }

    ProxyDataConfig ProxyDataConfig_;
    std::unordered_map<std::string,ProxyDataConfig ,std::hash<std::string>> ProxyPtrContainner;
    StreamBuilder * const StreamBuilderPtr;
    int ProxyId;

  };
}
#endif // BUILDERS_PROXY_H
