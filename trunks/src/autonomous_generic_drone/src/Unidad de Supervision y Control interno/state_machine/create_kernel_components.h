#ifndef CREATE_KERNEL_COMPONENTS_H
#define CREATE_KERNEL_COMPONENTS_H
#include <glog/logging.h>
#include "../../commonLibs/state_machine/generic_state_machine.h"
#include "../../commonLibs/factory/generic_factory.h"
#include "../servers_service/servers_manager.h"
#include "../state_machine/state_configurate_component.h"
namespace NSKernel
{
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
    NSServerManager::ServerManager<void>::factory_register;

    KERNEL::StateMachine<kernel>::changeState(aKernelPtr,&KERNEL::ConfigurateComponentState<kernel>::getStateInstance(),ErrorCode);
  }
  private:
  static void createInstance()
  {
      static CreateKernelComponents aInstance;
     StatePtr=&aInstance;
  }

  CreateKernelComponents():ErrorCode(0)
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
