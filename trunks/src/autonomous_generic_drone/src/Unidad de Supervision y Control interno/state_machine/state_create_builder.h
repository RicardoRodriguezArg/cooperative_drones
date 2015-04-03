/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief:
  *
  */
#ifndef STATE_CREATE_BUILDER_H
#define STATE_CREATE_BUILDER_H
#include <iostream>
#include <mutex>
#include <glog/logging.h>
#include "../commonLibs/state_machine/generic_state_machine.h"

#include "../commonLibs/builders/builders_streams.h"

#include "uc_definiciones.h"
//#include "state_shutdown_uc.h"
//#include "configurateKernelComponents.h"
//#include "state_create_kernel_component.h"

namespace KERNEL
{
template<class Kernel>
class  CreateBuilderState: public StateMachine<Kernel >
{
public:
    static CreateBuilderState & getState()
    {
        static std::mutex aLocalMutex;
        static std::lock_guard<std::mutex> lock(aLocalMutex);
        if(BuilderStatePtr==nullptr)
        {
            createInstance();
        }
        return * BuilderStatePtr;
     }
    static StateMachine<Kernel > * const getStatePtr()
    {
        static std::mutex aLocalMutex;
        static std::lock_guard<std::mutex> lock(aLocalMutex);
        if(BuilderStatePtr==nullptr)
        {
            createInstance();
        }
        return static_cast<StateMachine<Kernel > * > (BuilderStatePtr);
    }
    void releaseState()
    {
       ~CreateBuilderState();
    }

    void createBuilders( Kernel * const aKernelPtr ,int & aErrorCode )
    {
            LOG(INFO)<<"Buildenado las opciones de comunicacion"<<std::endl;
            StreamBuilder.buildAll(aErrorCode);
            LOG(INFO)<<"ErrorCode al crear StreamBuilder:  "<<aErrorCode<<std::endl;
           if(aErrorCode==ControlDef::ERROR_CODE::OK_ERROR_CODE)
            aKernelPtr->setBuilderInterface(ControlDef::BuilderName::StreamBuilder,&StreamBuilder);



        //creacion de builder finalizada
        //cambio a estado de configuracion de compoenntes
        //StateMachine<Kernel>::changeState(aKernelPtr,SADI_KERNEL::ConfigureKernelComponentState<Kernel>::getStatePtr(),_ErrorCode);
       // StateMachine<Kernel>::changeState(aKernelPtr,SADI_KERNEL::CreateKernelComponents<Kernel>::getStatePtr(),_ErrorCode);
        //
    }

    private:
    CreateBuilderState():_ErrorCode(0)
      ,StreamBuilder(ControlDef::ConfigFile::CommunicationXmlFile)
    {}
    ~CreateBuilderState()
    {
        isNullPtr=true;
        BuilderStatePtr=nullptr;
    }

    CreateBuilderState(const CreateBuilderState &) =delete;
    const CreateBuilderState & operator==(const CreateBuilderState &) = delete;
    CreateBuilderState(const CreateBuilderState &&) =delete;
    CreateBuilderState & operator==(const CreateBuilderState &&) = delete;
    static void createInstance()
    {
        static CreateBuilderState<Kernel> aBuilderState;
        BuilderStatePtr=(&aBuilderState);
        isNullPtr=false;
    }
    static void onDeadReference()
    {
    }
    static CreateBuilderState<Kernel> * BuilderStatePtr;
    static bool isNullPtr;
    int _ErrorCode;
    NSBuilders::Builders<NSCommonsLibs::BuilderType::StreamType> StreamBuilder;

};

template<class Kernel>
CreateBuilderState< Kernel > * CreateBuilderState<Kernel>::BuilderStatePtr=nullptr;
template<class Kernel>
bool CreateBuilderState<Kernel>::isNullPtr=true;
}
#endif // STATE_CREATE_BUILDER_H
