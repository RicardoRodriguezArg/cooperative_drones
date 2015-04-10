#ifndef STATE_TRANSITION_TRAITS_H
#define STATE_TRANSITION_TRAITS_H
#include <thread>
#include <chrono>
#include <mutex>
#include "state_transition_unit.h"
#include "../observer/sujeto.h"
namespace NSProtocol
{
  namespace
  {
   constexpr int OK_ERROR_CODE=0;
   constexpr unsigned sleep_time=100U;

  }
  template<class CmdStateModel,class ActionInterface,class StateInfo>
  class CmdState : public NSUtils::Sujeto<StateInfo>
  {

  public:
    enum class ECmdState
    {
      No_Init,
      Init,
      Running,
      Stopped
    };
    CmdState(CmdStateModel * const aCmdStateModelPtr,
             ActionInterface * const aActionInterfacePtr,
             const unsigned aMiliSleepTime):CmdStateModelManagerPtr(aCmdStateModelPtr)
                                                          ,CmdActionInterfacePtr(aActionInterfacePtr)
                                                          ,isRunning(false)
                                                          ,ErrorCode(OK_ERROR_CODE)
                                                          ,millisecond_sleep(aMiliSleepTime)
    {
      //CmdActionInterfacePtr->setModelPtr(CmdStateModelPtr);
    }

    void init()
    {
      CmdActionInterfacePtr->setInitcondition();
      while(isRunning)
        {
          CmdActionInterfacePtr->execute(isRunning);
          std::this_thread::sleep_for(millisecond_sleep);
          CmdStateModelManagerPtr->verifyCmdContext(CmdActionInterfacePtr->getCmdActionInfo,isRunning);
        }
      NSUtils::Sujeto<StateInfo>::notificarObservador(CmdActionInterfacePtr->getStateInfo(),ErrorCode);
    }

    void stopState()
    {
      isRunning=false;
    }

    void setCmdStateInfoUnit(const StateInfo & aCmdStateInfoModelUnit)
    {
      //eventManager
      CmdStateModelManagerPtr->UpdateRowStateInfo(aCmdStateInfoModelUnit);
    }
    bool isStateRunning()
    {
      return isRunning;
    }
    CmdStateModel * const CmdStateModelManagerPtr;
    ActionInterface * const CmdActionInterfacePtr;
    bool isRunning;
    int ErrorCode;
    const std::chrono::milliseconds millisecond_sleep;
  };


}
#endif // STATE_TRANSITION_TRAITS_H
