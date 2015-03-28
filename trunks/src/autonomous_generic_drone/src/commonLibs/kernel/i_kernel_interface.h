#ifndef I_KERNEL_INTERFACE_H
#define I_KERNEL_INTERFACE_H
#include <string>
namespace Kernel
{
    class IServiceTarget
    {
       public:
        virtual ~IServiceTarget(){}
        virtual void setRawMsg(std::string ) = 0;
    };
    class IKernelInterface
    {
       public:
        virtual ~IKernelInterface(){}
        virtual void init(int &) = 0;
        virtual void configurate(int &) = 0;
        virtual void stop(int &) = 0;
    };
}
#endif // I_KERNEL_INTERFACE_H
