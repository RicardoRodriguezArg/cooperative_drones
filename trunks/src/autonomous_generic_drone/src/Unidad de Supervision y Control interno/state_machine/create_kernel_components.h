#ifndef CREATE_KERNEL_COMPONENTS_H
#define CREATE_KERNEL_COMPONENTS_H

#include <mutex>
#include <glog/logging.h>
#include "uc_definiciones.h"
#include "../../commonLibs/factory/generic_factory.h"
#include "../../commonLibs/state_machine/generic_state_machine.h"
#include "../servers_service/servers_manager.h"
#include "../state_machine/state_configurate_component.h"
#include "../proxy_manager/proxy_manager.h"
#include "../../commonLibs/sub_cmds/sub_command_interface.h"
#include "../../commonLibs/sub_cmds/sub_cmds.h"
#include "../../commonLibs/mensajes/cpp/definicion_mensajeria.pb.h"
#include "../proxy/proxy.h"
#include "../proxy_manager/proxy_manager.h"
namespace NSKernel
{
  namespace
  {
    constexpr int STATE_OK_ERROR=0;
  }
  template<class kernel>
  class CreateKernelComponents : public KERNEL::StateMachine<kernel>
  {
    typedef NSSubCmds::SubCmds<Mensajes::MessageCommand> SubCmdType;
    typedef NSProxy::Proxy<SubCmdType,NSSubCmd::SubCmdInterface> ProxyType;
  public:
    static CreateKernelComponents & getInstance()
    {
      if(StatePtr==nullptr)
        {
          createInstance();
        }
      return * StatePtr;
    }
  void createKernelComponents(kernel * const aKernelPtr,int & aErrorCode)
  {
    LOG(INFO)<<"Creando los componenetes del nucleo";
    aErrorCode=STATE_OK_ERROR;
    createServerManagerComponent(aKernelPtr);
    createProxyManagerCompoenent(aKernelPtr);
    createDDSManagerProxy(aKernelPtr);
    createAutononousUnitControlProxy(aKernelPtr);
    LOG(INFO)<<"Fin de creacion de los componentes del nucleo, pasando al estado de Configuracion";
    KERNEL::StateMachine<kernel>::changeState(aKernelPtr,&KERNEL::ConfigurateComponentState<kernel>::getStateInstance(),ErrorCode);
  }
  private:
  void createServerManagerComponent(kernel * const aKernelPtr)
  {
    createKernelComponent<NSServerManager::ServerManager<void>>(aKernelPtr,"ServerManager");
  }
  void createDDSManagerProxy(kernel * const aKernelPtr)
  {
    createProxy(aKernelPtr,"DDSManagerProxy");
  }
  void createAutononousUnitControlProxy(kernel * const aKernelPtr)
  {
    createProxy(aKernelPtr,"AutonomousControlUnitProxy");
  }
  void createProxyManagerCompoenent(kernel * const aKernelPtr)
  {

    createKernelComponent<NSKernel::ProxyManager<ProxyType>>(aKernelPtr,"ProxyManager");
  }
  void createProxy(kernel * const aKernelPtr, const std::string & aProxyID)
  {
    LOG(INFO)<<"Creacion de proxy : "<<aProxyID;
    NSProxy::Proxy<SubCmdType,NSSubCmd::SubCmdInterface>::factory_register=KERNEL::FactoryRegister<NSProxy::Proxy<SubCmdType,NSSubCmd::SubCmdInterface>>(aProxyID);
    const auto aDDSManagerProxyptr=reinterpret_cast<ProxyType *>(KERNEL::KernelFactory::getInstance().getInstancePtr(aProxyID));
    const auto aProxyManagerPtr=aKernelPtr->getKernelDevice("ProxyManager");
    (reinterpret_cast<NSKernel::ProxyManager<ProxyType> *>(aProxyManagerPtr))->addProxy(aProxyID,aDDSManagerProxyptr);
  }
  template<typename ClassType>
  void createKernelComponent(kernel * const aKernelPtr, const std::string & aKernelDeviceDescription)
  {
    LOG(INFO)<<"Creacion de Componentes de Sistema: "<<aKernelDeviceDescription;
    ClassType::factory_register= KERNEL::FactoryRegister<ClassType>(aKernelDeviceDescription);
    const auto aProxyManagerPtr=KERNEL::KernelFactory::getInstance().getInstancePtr(aKernelDeviceDescription);
    aKernelPtr->setKernelInterface(aKernelDeviceDescription,aProxyManagerPtr);
  }
  static void createInstance()
  {
      static CreateKernelComponents aInstance;
     StatePtr=&aInstance;
  }

  CreateKernelComponents():ErrorCode(STATE_OK_ERROR)
  {}
  ~CreateKernelComponents()
  {}
  CreateKernelComponents(const CreateKernelComponents &) = delete;
  const CreateKernelComponents & operator==(const CreateKernelComponents &) = delete;
  CreateKernelComponents(const CreateKernelComponents &&) =delete;
  CreateKernelComponents & operator==(const CreateKernelComponents &&) = delete;

  static CreateKernelComponents<kernel> * StatePtr;
  int ErrorCode;
  };
  template<class Kernel>
  CreateKernelComponents<Kernel> * CreateKernelComponents<Kernel>::StatePtr=nullptr;
}
#endif // CREATE_KERNEL_COMPONENTS_H
