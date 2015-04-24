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
namespace NSKernel
{
  namespace
  {
    constexpr int STATE_OK_ERROR=0;
  }
  template<class kernel>
  class CreateKernelComponents : public KERNEL::StateMachine<kernel>
  {
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
    LOG(INFO)<<"Creacion de Manager de Server del sistema";
    NSServerManager::ServerManager<void>::factory_register=KERNEL::FactoryRegister<NSServerManager::ServerManager<void>>("ServerManager");
    LOG(INFO)<<"Creacion de los proxys del componente";
    LOG(INFO)<<"Creacion de los proxy DDS Manager";
    typedef NSSubCmds::SubCmds<Mensajes::MessageCommand> SubCmdType;
    NSProxy::Proxy<SubCmdType,NSSubCmd::SubCmdInterface>::factory_register=KERNEL::FactoryRegister<NSProxy::Proxy<SubCmdType,NSSubCmd::SubCmdInterface>>("DDSManagerProxy");
    LOG(INFO)<<"Creacion ProxyManager";

    LOG(INFO)<<"Fin de creacion de los componentes del nucleo, pasando al estado de Configuracion";
    KERNEL::StateMachine<kernel>::changeState(aKernelPtr,&KERNEL::ConfigurateComponentState<kernel>::getStateInstance(),ErrorCode);
  }
  private:
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
