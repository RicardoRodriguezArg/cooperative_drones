#ifndef CMD_PROCESSOR_H
#define CMD_PROCESSOR_H
#include "../../commonLibs/kernel/i_kernel_interface.h"
#include <iostream>
#include <mutex>
namespace NSCmdProcessor
{
template<class MsgType>
class CmdProcessor : public NSKernel::IServiceTarget
{
 public:
    static CmdProcessor & getInstance()
    {
            static std::mutex static_mutex;
            static std::lock_guard<std::mutex> lock(static_mutex);
            if(CmdProcessorPtr==nullptr)
            {
                createInstance();
            }
            return *CmdProcessorPtr;
    }
    void setRawMsg(std::string aMsg )
    {
        std::cout<<"llego mensaje !!!1"<<std::endl;
    }
private:
    CmdProcessor ()
    {}
    static void createInstance()
    {
         static CmdProcessor aInstance;
          CmdProcessorPtr=&aInstance;
    }
    static CmdProcessor  * CmdProcessorPtr;
};
template<class Msg>
CmdProcessor<Msg> * CmdProcessor<Msg>::CmdProcessorPtr=nullptr;
}
#endif // CMD_PROCESSOR_H
