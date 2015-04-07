#include "state_transition_unit.h"

namespace NSTest
{
  struct Options{};
  struct CurrentState{
    CurrentState(const Options * const)
    {}
  };
  struct Event{
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
  };
}
int main()
{
 const NSTest::Options aOptions;
 //NSTest::CurrentState * const aPtr = new NSTest::CurrentState(&aOptions);
  NSProtocol::StateTransitionUnit<NSTest::CurrentState,NSTest::Event,NSTest::NextState,NSTest::ActionInterface> aStateTransitionTable(&aOptions);

 return 0;
}
