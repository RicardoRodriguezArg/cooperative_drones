/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief:
  *
  */
#ifndef GENERIC_STATE_MACHINE_H
#define GENERIC_STATE_MACHINE_H

namespace KERNEL
{

template<class Kernel>
struct StateMachine
{

    /**
     * @brief createBuildersComponents definicion de la interface que implemntara cada estado
     * @param aErrorCode
     */
    virtual void createBuilders( Kernel * const aKernelPtr,int & aErrorCode)
    {
    }
    virtual void createKernelComponents(Kernel * const aKernelPtr,int & aErrorCode) {}
    virtual void configurateKernelComponents(Kernel * const aKernelPtr,int & aErrorCode)
    {
    }
    virtual void configureProxys(Kernel * const aKernelPtr,int & aErrorCode)
    {
    }
    virtual void buildMetaCmd(Kernel * const aKernelPtr,int & aErrorCode)
    {
    }
    virtual void runInitialSequence( Kernel * const aKernelPtr,int & aErrorCode)
    {
    }
    virtual void shutdownMode(Kernel * const aKernelPtr,int & aErrorCode)
    {
    }
    virtual void initComponents(Kernel * const aKernelPtr,int & aErrorCode){}
    virtual void OperativeState(Kernel * const aKernelPtr,int & aErrorCode) {}
    virtual void initialize_kernel(Kernel * const aKernelPtr,int & aErrorCode) {}
    virtual void iddle_state(Kernel * const aKernelPtr,int & aErrorCode) {}
protected:
     StateMachine()
     {}
    void changeState(Kernel * const aKernelPtr, StateMachine * const aStatePtr, int & aErrorCode)
    {
        if(aKernelPtr!=nullptr && aStatePtr != nullptr)
        {
            aKernelPtr->setState(aStatePtr);
        }
    }


};

}
#endif // GENERIC_STATE_MACHINE_H
