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
   constexpr unsigned sleep_time=100;
   constexpr std::chrono::milliseconds millisecond_sleep(sleep_time);
  }
  template<class EventState,class CmdStateModel,class ActionInterface,class Event>
  class CmdState : public NSUtils::Sujeto<Event>
  {

  public:
    CmdState(CmdStateModel * const aCmdStateModelPtr,
             ActionInterface * const aActionInterfacePtr):CmdStateModelPtr(aCmdStateModelPtr)
                                                          ,CmdActionInterfacePtr(aActionInterfacePtr)
                                                          ,isRunning(false)
                                                          ,ErrorCode(OK_ERROR_CODE)
    {
        CmdActionInterfacePtr->setModelPtr(CmdStateModelPtr);
    }
    void init()
    {
      CmdActionInterfacePtr->setInitcondition();
      while(isRunning)
        {
          CmdActionInterfacePtr->execute(isRunning);
          std::this_thread::sleep_for(millisecond_sleep);
          CmdActionInterfacePtr->verifyCmdContext(isRunning);
        }
      NSUtils::Sujeto<Event>::notificarObservador(CmdActionInterfacePtr->getEventInfo(),ErrorCode);
    }
    void stopState()
    {
      isRunning=false;
    }

    template<typename ModelUnitType>
    void setCmdStateModel(const ModelUnitType & aUnitModelType)
    {
      //eventManager
      CmdStateModelPtr->setUnit(aUnitModelType);
    }
    EventState eventManager;
    CmdStateModel * const CmdStateModelPtr;
    ActionInterface * const CmdActionInterfacePtr;
    volatile bool isRunning;
    int ErrorCode;
  };


}
#endif // STATE_TRANSITION_TRAITS_H
