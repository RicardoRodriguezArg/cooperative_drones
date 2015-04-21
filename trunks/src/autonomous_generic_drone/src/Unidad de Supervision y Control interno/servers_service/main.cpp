#include "../../commonLibs/factory/generic_factory.h"
#include "servers_manager.h"

int main()
{

  KERNEL::KernelFactory::getInstance();
  NSServerManager::ServerManager<void>::factory_register;
 return 0;
}
