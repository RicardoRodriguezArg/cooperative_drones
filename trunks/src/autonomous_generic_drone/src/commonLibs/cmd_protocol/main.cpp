/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-04-2015
  *@brief:
  *
  */
#include "state_transition_unit.h"

namespace NSTest
{
  struct Options{};
  struct CurrentState{
    CurrentState(const Options * const)
    {}
    struct ActionInterface{
      ActionInterface(const Options * const)
      {

      }
    };

  };
  struct Event{
    Event()
    {}
    Event(const Options * const)
    {}
  };
  struct NextState{
    NextState(const Options * const)
    {}
  };
  struct ActionInterface{
    ActionInterface(const Options * const)
    {}
    struct CurrentStateAction{
      CurrentStateAction(const Options * const){}
    };
  };
}
int main()
{
 const NSTest::Options aOptions;
 //NSTest::CurrentState * const aPtr = new NSTest::CurrentState(&aOptions);
  NSProtocol::StateRow<NSTest::CurrentState,NSTest::Event> aStateTransitionTable(&aOptions);


 return 0;
}
