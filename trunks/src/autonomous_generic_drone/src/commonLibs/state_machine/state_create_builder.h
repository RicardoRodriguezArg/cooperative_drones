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
#include "generic_state_machine.h"
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

    void createBuilders( Kernel * const aKernelPtr
            ,int & aErrorCode )
    {

		//        aKernelPtr->setBuilderInterface(EKERNEL_BUILDERS::EKERNEL_BUILDERS_MODEL_PROPERTIES_MAP, 		//static_cast<IBuilderInterface *>(&aModelPropertiesBuilder));
        //falta agregarlo en el mapa


        //creacion de builder finalizada
        //cambio a estado de configuracion de compoenntes
        //StateMachine<Kernel>::changeState(aKernelPtr,SADI_KERNEL::ConfigureKernelComponentState<Kernel>::getStatePtr(),_ErrorCode);
       // StateMachine<Kernel>::changeState(aKernelPtr,SADI_KERNEL::CreateKernelComponents<Kernel>::getStatePtr(),_ErrorCode);
        //
    }

    private:
    CreateBuilderState():_ErrorCode(0)
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
};

template<class Kernel>
CreateBuilderState< Kernel > * CreateBuilderState<Kernel>::BuilderStatePtr=nullptr;
template<class Kernel>
bool CreateBuilderState<Kernel>::isNullPtr=true;
}
#endif // STATE_CREATE_BUILDER_H
