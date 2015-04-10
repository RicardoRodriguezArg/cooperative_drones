#ifndef STATE_CONFIGURATE_COMPONENT_H
#define STATE_CONFIGURATE_COMPONENT_H
#include <mutex>
#include <glog/logging.h>
#include "uc_definiciones.h"
#include "../servers_service/servers_manager.h"
#include "../commonLibs/state_machine/generic_state_machine.h"
#include "../../commonLibs/factory/generic_factory.h"
#include "../cmd_processor/cmd_processor.h"
namespace KERNEL
{
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
        configurateServerManager(aKernelPtr);

    }
private:
    ConfigurateComponentState()
    {}
    void configurateServerManager(Kernel * const aKernelPtr)
    {
        const auto Ptr=(KERNEL::KernelFactory::getInstance().createInstance("ServerManager").get());

        reinterpret_cast<NSServerManager::ServerManager * >(Ptr)->getReactor()->make_service_tuple(nullptr,&NSCmdProcessor::CmdProcessor::getInstance());
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
};
template<class Kernel>
ConfigurateComponentState< Kernel > * ConfigurateComponentState<Kernel>::statePtr=nullptr;
}
#endif // STATE_CONFIGURATE_COMPONENT_H
