#ifndef GENERIC_FACTORY_H
#define GENERIC_FACTORY_H
#include <string>
#include <memory>
#include <functional>
#include <mutex>
#include "base_class.h"
namespace KERNEL
{
    /**
      @brief clase Factory Generica utilizada para realizar la construccion de los componentes del kernel
      */

    class KernelFactory
    {
        public:
            static KernelFactory & getInstance()
            {
                static std::mutex factory_mutex;
                static std::lock_guard<std::mutex> lock(factory_mutex);
                if(KenelPtr==nullptr)
                {
                    createFactoryInstance();
                }
                return *KenelPtr;
            }
            void registerFactoryFunction(const std::string & aStringKey, std::function<FactoryBase *()> aClassFactoryFunctor)
            {
                FactoryRegistryMap[aStringKey]=aClassFactoryFunctor;
            }
            std::shared_ptr<FactoryBase>   createInstance(const std::string & aClassName)
            {
               FactoryBase *  instance_ptr=nullptr;
               const auto iter= FactoryRegistryMap.find(aClassName );
               if(iter!=FactoryRegistryMap.end())
               {
                   instance_ptr=iter->second();
                 }

               //TODO: multiples retornos
               if(instance_ptr!=nullptr)
                   return std::shared_ptr<FactoryBase > (instance_ptr);
               else return nullptr;
            }
        private:
            KernelFactory()
            {}
            ~KernelFactory()
            {}
            static void createFactoryInstance()
            {
                static KernelFactory aKernel;
                KenelPtr=&aKernel;
                IsNullPtr=true;
            }
            std::unordered_map<std::string,std::function<FactoryBase * ()>> FactoryRegistryMap;
            static KernelFactory * KenelPtr;
            static bool IsNullPtr;
    };
    KernelFactory *  KernelFactory::KenelPtr=nullptr;
    bool KernelFactory::IsNullPtr=true;
}
#endif // GENERIC_FACTORY_H
