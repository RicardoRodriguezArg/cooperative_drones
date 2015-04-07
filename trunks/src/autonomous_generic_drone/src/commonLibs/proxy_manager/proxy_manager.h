#ifndef PROXY_MANAGER_H
#define PROXY_MANAGER_H
#include <unordered_map>

namespace NSProxyManager
{
  template<class Proxy>
  class ProxyManager
  {
  public:
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
