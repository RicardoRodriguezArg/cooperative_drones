#ifndef PROXY_MANAGER_C_H
#define PROXY_MANAGER_C_H
#include "../../commonLibs/proxy_manager/proxy_manager.h"
#include "../../commonLibs/factory/base_class.h"
#include "../../commonLibs/factory/factory_register.h"
namespace NSKernel
{
  template<class ProxyType>
  class ProxyManager : public NSCommonLibs::ProxyManagerBase<ProxyType> ,public KERNEL::FactoryBase
  {
  public:
  private:

  };
}
#endif // PROXY_MANAGER_H
