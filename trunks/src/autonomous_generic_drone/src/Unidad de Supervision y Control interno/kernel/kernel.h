#ifndef KERNEL_H
#define KERNEL_H
#include <unordered_map>
#include <stdexcept>
#include <glog/logging.h>
#include "uc_definiciones.h"

#include "../../commonLibs/factory/generic_factory.h"
#include "../../commonLibs/builders/builders_streams.h"
#include "../../commonLibs/kernel/i_kernel_interface.h"

#include "../state_machine/state_create_builder.h"
#include "../state_machine/create_kernel_components.h"
#include "../state_machine/state_configurate_component.h"
#include "../cmd_processor/cmd_processor.h"


namespace NSUC_Kernel
{
//TODO: Normalizar los mensajes de excepcion, crear tabla de texto de excepciones

class Kernel
{
    public:
    Kernel():CurrentState(&KERNEL::CreateBuilderState<Kernel>::getState())
      ,ErrorCode(ControlDef::ERROR_CODE::OK_ERROR_CODE)
    {
      //creacion de las instancias de los estados
      KERNEL::ConfigurateComponentState<Kernel>::getStateInstance();
    }
    ~Kernel()
    {
      //borrar punteros de los componentes del nucleo
    }
    void init()
    {
         CurrentState->createBuilders(this,ErrorCode);
         if(ErrorCode!=0) throw std::logic_error("Error al inicializar el sistema, verifique path archivo de configuracion");

    }
    void createKernelDevices()
    {
      CurrentState->createKernelComponents(this,ErrorCode);
      if(ErrorCode!=0) throw std::logic_error("Error al crear las instancias de los componentes del kernel");
    }
    void configurateKernelComponents()
    {
        CurrentState->configurateKernelComponents(this,ErrorCode);
        if(ErrorCode!=0) throw std::logic_error("Error al configurar el estado configurateKernelComponents");
    }
    void shutdownKernelComponents()
    {
      CurrentState->shutdownMode(this,ErrorCode);
      if(ErrorCode!=0) throw std::logic_error("Error al detener los procesos del kernel ");
    }

    void setBuilderInterface(const std::string & aBuilderName, NSBuilders::IBuilderInterface * const  aBuilderPtr)
    {
            builders_map.insert(std::make_pair(aBuilderName,aBuilderPtr));
    }
    void setKernelInterface(const std::string & aKernelDeviceDescription, KERNEL::FactoryBase * const aKernelDevicePointer)
    {
      kernel_device_map.insert(std::make_pair(aKernelDeviceDescription,aKernelDevicePointer));
    }
    KERNEL::FactoryBase * getKernelDevice(const std::string & aKernelDeviceDescription)
    {
      const auto iterator=kernel_device_map.find(aKernelDeviceDescription);
      KERNEL::FactoryBase * returnPtr=nullptr;
      if(iterator!=kernel_device_map.end())
        {
          returnPtr=iterator->second;
        }
      else throw std::logic_error("Error al buscar device en mapa de kernel, descripcion de dispositvo de kernel no corresponde a ninguna en mapa");
      return returnPtr;

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
        NSCmdProcessor::CmdProcessor<void>::getInstance();

    }
    static void initLogging()
    {
       //GOOGLE_PROTOBUF_VERIFY_VERSION;
         google::InitGoogleLogging("unidad_control");
    }
    void setState(KERNEL::StateMachine<Kernel> * const aCurrentState)
    {
        CurrentState=aCurrentState;
    }
    void stopKernelProcess()
    {
      //for(auto iterator= kernel_device_map.begin();)
    }
    private:
    KERNEL::StateMachine<Kernel> * CurrentState;
    int ErrorCode;
    std::unordered_map<std::string, NSBuilders::IBuilderInterface * const> builders_map;
    std::unordered_map<std::string,KERNEL::FactoryBase * const  > kernel_device_map;
};
}
#endif // KERNEL_H
