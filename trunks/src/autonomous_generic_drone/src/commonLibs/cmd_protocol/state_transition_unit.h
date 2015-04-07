#ifndef CMD_PROTOCOL_H
#define CMD_PROTOCOL_H
#include <tuple>
namespace NSProtocol
{
  //base Case
  template< class ... Others
           >
  class StateTransitionUnit{}; //definicion de clase vacia


  template<class CurrentState,
           class Event,
           class NextState,
           class ActionInterface,
           class ... Others
           >
  class StateTransitionUnit<CurrentState,Event,NextState,ActionInterface,Others...>
  {
  public:
    template<typename Options >
    StateTransitionUnit(const Options * const aOptionsPtr):currentState(aOptionsPtr)
    ,eventState(aOptionsPtr)
    ,nextState(aOptionsPtr)
    ,action(aOptionsPtr)
    ,Row(&currentState,&eventState,&nextState,&action)
    {}
      private:
    CurrentState currentState;
    Event eventState;
    NextState nextState;
    ActionInterface action;
    const std::tuple<CurrentState * ,Event * const ,NextState * const ,ActionInterface  * const > Row;
  };
}
#endif // CMD_PROTOCOL_H
