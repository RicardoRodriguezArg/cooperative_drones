#ifndef CMD_PROTOCOL_H
#define CMD_PROTOCOL_H
#include <tuple>
#include <unordered_map>
#include "../utils_generics/generis_strutures.h"
namespace NSProtocol
{
  //base Case
  template< class ... Others
           >
  class StateRow{}; //definicion de clase vacia
  //class Forwarding
  class Event;

  template<class State,
           class StateEvents,
           class ... Others
           >
  class StateRow<State,StateEvents,Others...>
  {
    public:
    enum class EStateID
    {
      currentState,
      nextState
    };
    enum class EStateAction
    {
      start,
      transition_action,
      stop
    };
    typedef std::tuple<EStateID, EStateAction> tuple_key_type;
    typedef typename State::ActionInterface ActionInterface;
    typedef  std::unordered_map< const tuple_key_type, ActionInterface * const ,NSUtils::tuple_key_hash<tuple_key_type>,NSUtils::tuple_key_equal<tuple_key_type>>  ActionMapType;

    //protected:
    public:
    template<typename Options >
    StateRow(const Options * const aOptionsPtr =nullptr,State * const aNextState =nullptr):currentState(aOptionsPtr)
    ,NextState(aNextState)
    {
    }
    StateRow():
    NextState(nullptr)
    {
    }
    virtual ~StateRow(){}
    virtual void checkEvent(Event * const eventRecieved)
    {
    }
    void setStateMap(ActionMapType * const aStateMapPtr)
    {
      stateActionMap=aStateMapPtr;
    }
    void setNextState(State * const aNextState)
    {
        NextState=aNextState;
    }
    State * const getNextState() const
    {
      return NextState;
    }

    void setStateActions(const EStateID & aStateID,const EStateAction & ActionState, ActionInterface * const aActionInterface )
    {
      stateActionMap.insert(std::make_tuple(std::make_tuple(aStateID,ActionState),aActionInterface));
    }

    void executeActions(const EStateID & aStateID,const EStateAction & ActionState, int & aErrorCode)
    {
      const auto aTuple=std::make_tuple(aStateID,ActionState);
      const auto iterator = stateActionMap.find(aTuple);
      if(iterator!= stateActionMap.end())
        {
          (iterator->second)->execute(aErrorCode);
        }
    }


    State currentState;
    State *  NextState;
    StateEvents StateEventsManager;
    ActionMapType stateActionMap;

  };
}
#endif // CMD_PROTOCOL_H
