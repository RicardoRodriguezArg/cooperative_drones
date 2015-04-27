#ifndef STATE_SHUTDOWN_H
#define STATE_SHUTDOWN_H
#include <mutex>
#include <glog/logging.h>
#include "uc_definiciones.h"
#include "../commonLibs/state_machine/generic_state_machine.h"
namespace KERNEL
{
  template<class Kernel>
  class  ShutdownState: public StateMachine<Kernel >
  {
  public:
    static ShutdownState & getStateInstance()
    {
        static std::mutex aLocalMutex;
        static std::lock_guard<std::mutex> lock(aLocalMutex);
        if(BuilderStatePtr==nullptr)
        {
            createInstance();
        }
        return * BuilderStatePtr;
    }
    void shutdownMode(Kernel * const aKernelPtr,int & aErrorCode)
    {
      aErrorCode=0;
      aKernelPtr->stopKernelProcess();
    }
  private:
    ShutdownState()

    {}
    ~ShutdownState()
    {
      isNullPtr=true;
      BuilderStatePtr=nullptr;
    }
    static void createInstance()
    {
        static ShutdownState<Kernel> aBuilderState;
        BuilderStatePtr=(&aBuilderState);
        isNullPtr=false;
    }

    ShutdownState(const ShutdownState &) =delete;
    const ShutdownState & operator==(const ShutdownState &) = delete;
    ShutdownState(const ShutdownState &&) =delete;
    ShutdownState & operator==(const ShutdownState &&) = delete;

    static ShutdownState<Kernel> * BuilderStatePtr;
    static bool isNullPtr;
    int _ErrorCode;
  };
  template<class Kernel>
  ShutdownState< Kernel > * ShutdownState<Kernel>::BuilderStatePtr=nullptr;
  template<class Kernel>
  bool ShutdownState<Kernel>::isNullPtr=true;
}
#endif // STATE_SHUTDOWN_H
