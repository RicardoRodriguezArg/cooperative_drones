#ifndef PROXY_H
#define PROXY_H
#include "../../commonLibs/proxy_base/proxy_base.h"
#include "../../commonLibs/kernel/i_kernel_interface.h"
#include "../../commonLibs/comunicacion/icomm.h"
#include "../../commonLibs/proxy_base/i_proxy_proccess.h"
#include "../../commonLibs/sub_cmds/sub_cmds.h"
#include "../../commonLibs/mensajes/cpp/definicion_mensajeria.pb.h"
//registrar en la clase factory

#include "uc_definiciones.h"

namespace NSProxy
{
  //TODO: Falta completar esta clase
  //Falta los mensajes creados con Protocol Buffer
template<class SubCmdType, class SubCmdInterface>
class Proxy :  ProxyBase< NSKernel::ISerializer
                              ,  COMUNICACION::IComm
                              ,  IProxyProcess<Proxy<SubCmdType,SubCmdInterface>>
                              ,  NSKernel::IServiceTarget
                              >
{

public:
  Proxy(const unsigned & aProxyId):ProxyBase(aProxyId)
  {}
  void execute( SubCmdType aCmd, int &)
  {
    //NSProxy::ProxyBase::Buffer.clear();
    //aca un reinterpreter cast para ese dato en particular
    //Buffer=ProxyBase::MsgSerializerMap[ControlDef::NSProxy::CMD_TYPE_ID]->serializeData();
  }

  SubCmdInterface  * geSubCmd(const std::string &) const
  {

  }
private:

};
}
#endif // PROXY_H
