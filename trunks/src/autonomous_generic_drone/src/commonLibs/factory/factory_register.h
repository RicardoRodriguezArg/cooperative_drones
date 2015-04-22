#ifndef FACTORY_REGISTER_H
#define FACTORY_REGISTER_H
#include "generic_factory.h"
#include <iostream>
#include <glog/logging.h>
namespace KERNEL
{
  template<class Type>
    class  FactoryRegister
    {
    public:
        explicit FactoryRegister(const std::string & aClassName)
        {
            LOG(INFO)<<"Registrando Objecto en Fabrica(Nombre de la clase: ): "<<aClassName;
            KernelFactory::getInstance().registerFactoryFunction(aClassName,[](void)->FactoryBase *
              {
                auto ptr= new Type();
                return reinterpret_cast<KERNEL::FactoryBase *>(ptr);
              }
            );
        }
    };


}
#endif // FACTORY_REGISTER_H
