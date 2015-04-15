#ifndef BUILDER_PROXY_INFO_H
#define BUILDER_PROXY_INFO_H
#include <string>
#include <vector>
#include "../utils_generics/generis_strutures.h"
/*
 *AL PEDO!!!!!
 **/
namespace NSBuilders
{
  namespace
  {
    constexpr unsigned DEFAULT_PROXY_ID=0U;
  }

  class ProxyInfo
  {
    enum DATA_TYPE_INDEX
    {
      CONNECTOR_DATA_TYPE_INDEX=0,
      CONNECTOR_IP_INDEX,
      CONNECTOR_PORT_PORT,
      CONNECTOR_END_INDEX

    };
    typedef unsigned id_type;
    typedef std::tuple<std::string, std::string, std::string> InfoUnitType;
    public:
    ProxyInfo():ProxyId(DEFAULT_PROXY_ID)
    {}
    void setProxyID(const id_type & aID)
    {
      ProxyId=aID;
    }

    id_type getProxyId() const
    {
      return ProxyId;
    }

    std::vector<InfoUnitType> getProxyOptions() const
    {
      return proxy_info_vector_;
    }
    void setConnectorStreamType(const std::string& connector_data_type, const std::string & connector_ip, const std::string & port)
    {
      const auto aTuple=std::make_tuple(connector_data_type,connector_ip,port);
      proxy_info_vector_.emplace_back(aTuple);
    }
    void clear()
    {
      ProxyId=DEFAULT_PROXY_ID;
      for ( auto iterator = proxy_info_vector_.begin();iterator!=proxy_info_vector_.end();iterator++)
        {

        //NSUtils::tuple_iterator(static_cast<InfoUnitType>(*iterator),NSUtils::clean_tuple<std::string>);
          auto tuple_info=*iterator;
          std::get<CONNECTOR_DATA_TYPE_INDEX>(tuple_info).clear();
          std::get<CONNECTOR_IP_INDEX>(tuple_info).clear();
          std::get<CONNECTOR_PORT_PORT>(tuple_info).clear();
        };

    }
     std::vector<InfoUnitType> * getProxyInfo()
    {
      return &proxy_info_vector_;
    }
    private:
    id_type ProxyId;
    std::vector<InfoUnitType> proxy_info_vector_;
  };
}
#endif // BUILDER_PROXY_INFO_H
