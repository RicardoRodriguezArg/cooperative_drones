#ifndef SUB_COMMAND_INTERFACE_H
#define SUB_COMMAND_INTERFACE_H
namespace NSSubCmd
{
  struct SubCmdInterface
  {
    virtual ~SubCmdInterface(){}
    virtual int getSubCmdId() = 0 ;
  };
}
#endif // SUB_COMMAND_INTERFACE_H
