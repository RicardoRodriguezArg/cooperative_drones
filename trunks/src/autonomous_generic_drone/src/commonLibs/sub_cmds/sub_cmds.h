/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-04-2015
  *@brief:
  *
  */
#ifndef SUB_CMDS_H
#define SUB_CMDS_H
namespace NSSubCmds
{
  //TODO:Definir esta clase, definir los procesos para los subcmds
  template<class CmdType>
class SubCmds
{
public:
  SubCmds()
  {}
  CmdType * getCmdType() const
  {
    return CmdTypePtr;
  }
  CmdType * const CmdTypePtr;
};
}
#endif // SUB_CMDS_H
