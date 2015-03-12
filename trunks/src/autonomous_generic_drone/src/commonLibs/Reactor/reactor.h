/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief: Clase que representa la capa reactiva del patron acceptor - connector. Implementada con variadic templates .
  *
  */
#ifndef REACTOR_H
#define REACTOR_H
#include <unordered_map>
namespace NSReactorLayer
{
  //Base Type Definitions
  template<typename ... MsgTypesStruct>
  class Reactor{};

  template<typename MsgTypesStruct, typename ... OtherMsgTypesStruct>
  class Reactor
  {
  public:
    Reactor()
    {}
    private:
    std::unordered_map<typename MsgTypesStruct::Index,typename MsgTypesStruct::NodeTuple,typename MsgTypesStruct::Hashfunction> MsgTypesMap;
  };
}
#endif // REACTOR_H
