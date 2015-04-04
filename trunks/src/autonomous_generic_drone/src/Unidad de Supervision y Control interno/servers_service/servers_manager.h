#ifndef SERVERS_MANAGER_H
#define SERVERS_MANAGER_H
#include "uc_definiciones.h"
#include "../../commonLibs/kernel/i_kernel_interface.h"
#include "../../commonLibs/factory/base_class.h"
#include "../../commonLibs/factory/factory_register.h"
#include "../../commonLibs/Reactor/reactor.h"
#include "../../commonLibs/comunicacion/icomm.h"
namespace NSServerManager
{
class ServerManager : public KERNEL::FactoryBase, public NSKernel::IKernelInterface
{
public:
    ServerManager():ErrorCode(ControlDef::ERROR_CODE::OK_ERROR_CODE)
    {}
    virtual int getID()
    {
            return ControlDef::ClassID::SERVER_MANAGER_ID;
    }
     void init(int &)
     {
         reactor_layer.initCommServices();
         reactor_layer.init();
     }
     void configurate(int &)
     {}
     void stop(int &)
     {
         reactor_layer.stop();
     }
     NSReactorLayer::Reactor<COMUNICACION::IComm,NSKernel::IServiceTarget> * getReactor()
     {
         return &reactor_layer;
     }
    private:
     NSReactorLayer::Reactor<COMUNICACION::IComm,NSKernel::IServiceTarget> reactor_layer;
     int ErrorCode;
     static KERNEL::FactoryRegister< ServerManager> factory_register;
     static bool isRegisterDone;
};
 KERNEL::FactoryRegister< ServerManager> ServerManager::factory_register("ServerManager");
 bool ServerManager::isRegisterDone=true;
}
#endif // SERVERS_MANAGER_H
