/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-04-2015
  *@brief:
  *
  */
#ifndef PROXY_MANAGER_H
#define PROXY_MANAGER_H
#include <unordered_map>

namespace NSCommonLibs
{
  template<class Proxy>
  class ProxyManager
  {
  protected:
    ProxyManager()
    {}
    void addProxy(const std::string & aProxyID,Proxy * const aProxyPtr)
    {
      ProxyMap.insert(std::make_pair(aProxyID,aProxyPtr));
    }
    Proxy * const getProxy(const std::string & aProxyID)
    {
      const auto iterator = ProxyMap.find(aProxyID);
      Proxy * aPtr=nullptr;
      if (iterator!=ProxyMap.end())
        {
            aPtr=(iterator->second);
        }
      return aPtr;
    }
  private:
    std::unordered_map<const std::string,Proxy * const> ProxyMap;

  };
}
#endif // PROXY_MANAGER_H
