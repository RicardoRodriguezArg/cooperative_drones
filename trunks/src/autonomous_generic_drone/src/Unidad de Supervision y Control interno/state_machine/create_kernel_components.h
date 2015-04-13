#ifndef CREATE_KERNEL_COMPONENTS_H
#define CREATE_KERNEL_COMPONENTS_H
#include "../../commonLibs/state_machine/generic_state_machine.h"
namespace NSKernel
{
  template<class kernel>
  class CreateKernelComponents : public KERNEL::StateMachine<kernel>
  {
  public:
  void createKernelComponents(kernel * const aKernelPtr,int & aErrorCode)
  {

  }
  private:
  };
}
#endif // CREATE_KERNEL_COMPONENTS_H
