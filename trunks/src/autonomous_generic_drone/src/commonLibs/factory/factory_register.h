#ifndef FACTORY_REGISTER_H
#define FACTORY_REGISTER_H
#include "generic_factory.h"

namespace KERNEL
{
  template<class Type>
    class  FactoryRegister
    {
    public:
        explicit FactoryRegister(const std::string & aClassName)
        {
            KernelFactory::getInstance().registerFactoryFunction(aClassName,[](void)->FactoryBase *{return new Type();});
        }
    };

}
#endif // FACTORY_REGISTER_H
