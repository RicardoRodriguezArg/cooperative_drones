#ifndef STATE_CONFIGURATE_COMPONENT_H
#define STATE_CONFIGURATE_COMPONENT_H
#include <mutex>
#include <glog/logging.h>
#include "uc_definiciones.h"
#include "../../commonLibs/factory/generic_factory.h"
#include "../../commonLibs/builders/builders_streams.h"

#include "../commonLibs/state_machine/generic_state_machine.h"
#include "../cmd_processor/cmd_processor.h"
#include "../servers_service/servers_manager.h"
#include "../proxy/proxy.h"
#include "state_shutdown.h"
namespace KERNEL
{
  namespace
  {
  constexpr int STATE_ERROR=-1;
  constexpr int STATE_OK=0;
  }
template<class Kernel>
class  ConfigurateComponentState: public StateMachine<Kernel >
{


       public:
    static ConfigurateComponentState & getStateInstance()
    {
        static std::mutex stattic_mutex;
        static std::lock_guard<std::mutex> lock(stattic_mutex);
        if(statePtr==nullptr)
        {
            createInstance();
        }
        return *statePtr;
    }
    void configurateKernelComponents(Kernel * const aKernelPtr,int & aErrorCode)
    {
        //configurando el server manager
        configurateServerManager(aKernelPtr,aErrorCode);

        KERNEL::StateMachine<Kernel>::changeState(aKernelPtr,&KERNEL::ShutdownState<Kernel>::getStateInstance(),ErrorCode);

    }
    void releaseState()
    {
       ~ConfigurateComponentState();
    }
private:
    ConfigurateComponentState():ErrorCode(0)
    {}

    ~ConfigurateComponentState()
    {
      statePtr=nullptr;
    }
    void configurateServerManager(Kernel * const aKernelPtr,int & aErrorCode)
    {
      LOG(INFO)<<"Creacion de servidores del sistema";
        aErrorCode=STATE_ERROR;
        const auto ptr=aKernelPtr->getKernelDevice("ServerManager");
        const auto aBuilderPtr=aKernelPtr->getBuilderInterface(ControlDef::BuilderName::StreamBuilder);
        const auto aStreammerBuilder=reinterpret_cast<NSBuilders::Builders<NSCommonsLibs::BuilderType::StreamType> *>(aBuilderPtr);
        const auto aCommandServerPtr=aStreammerBuilder->getComInterface("USyCI","in","command");//servidor de comandos
        if(aCommandServerPtr!=nullptr)
          {
            aErrorCode=STATE_OK;
            const auto aCmdProceesorPtr=&NSCmdProcessor::CmdProcessor<void>::getInstance();
            LOG(INFO)<<"Vinculando CommandProcessor con stream In";
           (reinterpret_cast<NSServerManager::ServerManager<void> * >(ptr))->getReactor()->make_service_tuple(aCommandServerPtr,aCmdProceesorPtr);

          }
        LOG(INFO)<<"Fin de creacion de servidores del sistema";

    }
    void configurateProxy(Kernel * const aKernelPtr,const std::string & aProxyID, int & aErrorCode)
    {
      const auto aBuilderPtr=aKernelPtr->getBuilderInterface(ControlDef::BuilderName::StreamBuilder);
      const auto aStreammerBuilder=reinterpret_cast<NSBuilders::Builders<NSCommonsLibs::BuilderType::StreamType> *>(aBuilderPtr);

      const auto aConnectorPtr=aStreammerBuilder->getComInterface(aProxyID,"out","command");//servidor de comandos
      //Configuracion atravez del proxymanager
      //const auto ptr=aKernelPtr->getKernelDevice("ProxyManager");
    }
    static void createInstance()
    {
        static ConfigurateComponentState aInstance;
       statePtr=&aInstance;
    }
    ConfigurateComponentState(const ConfigurateComponentState &) = delete;
    const ConfigurateComponentState & operator==(const ConfigurateComponentState &) = delete;
    ConfigurateComponentState(const ConfigurateComponentState &&) =delete;
    ConfigurateComponentState & operator==(const ConfigurateComponentState &&) = delete;

    static ConfigurateComponentState<Kernel> *  statePtr;
    int ErrorCode;
};
template<class Kernel>
ConfigurateComponentState< Kernel > * ConfigurateComponentState<Kernel>::statePtr=nullptr;
}
#endif // STATE_CONFIGURATE_COMPONENT_H
