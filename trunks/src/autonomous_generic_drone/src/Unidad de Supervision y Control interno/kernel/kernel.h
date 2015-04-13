#ifndef KERNEL_H
#define KERNEL_H
#include <unordered_map>
#include <glog/logging.h>
#include "uc_definiciones.h"
#include "../../commonLibs/builders/builders_streams.h"
#include "../../commonLibs/kernel/i_kernel_interface.h"
#include "../../commonLibs/factory/generic_factory.h"
#include "../state_machine/state_create_builder.h"
#include "../state_machine/state_configurate_component.h"
#include "../cmd_processor/cmd_processor.h"
namespace NSUC_Kernel
{

class Kernel
{
    public:
    Kernel():CurrentState(&KERNEL::CreateBuilderState<Kernel>::getState())
      ,ErrorCode(ControlDef::ERROR_CODE::OK_ERROR_CODE)
    {}
    void init()
    {
        LOG(INFO)<<"iniciando la creacion de los builders del sistema";
        CurrentState->createBuilders(this,ErrorCode);
        LOG(INFO)<<"ErrorCode al crear los builders: "<<ErrorCode;
    }
    void configurateKernelComponents()
    {
        LOG(INFO)<<"Configurando los componentes del sistema";
    }

    void setBuilderInterface(const std::string & aBuilderName, NSBuilders::IBuilderInterface * const  aBuilderPtr)
    {
            builders_map.insert(std::make_pair(aBuilderName,aBuilderPtr));
    }
    NSBuilders::IBuilderInterface * getBuilderInterface(const std::string & aBuilderName)
    {
      NSBuilders::IBuilderInterface * aBuilderPtr=nullptr;
      const auto iterator=builders_map.find(aBuilderName);
      if(iterator!=builders_map.end())
        {
          aBuilderPtr=iterator->second;
        }
      return aBuilderPtr;
    }
    static void initSystemSingletons()
    {
        initLogging();
        KERNEL::KernelFactory::getInstance();
        NSCmdProcessor::CmdProcessor::getInstance();

    }
    static void initLogging()
    {
       //GOOGLE_PROTOBUF_VERIFY_VERSION;
         google::InitGoogleLogging("unidad_control");
    }
    private:
    KERNEL::StateMachine<Kernel> * CurrentState;
    int ErrorCode;
    std::unordered_map<std::string, NSBuilders::IBuilderInterface * const> builders_map;
};
}
#endif // KERNEL_H
