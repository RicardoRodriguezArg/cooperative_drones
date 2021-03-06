#ifndef GENERIC_FACTORY_H
#define GENERIC_FACTORY_H
#include <string>
#include <memory>
#include <functional>
#include <glog/logging.h>
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
              LOG(INFO)<<"registerFactoryFunction";
                FactoryRegistryMap[aStringKey]=aClassFactoryFunctor;
            }
            std::shared_ptr<FactoryBase>   createInstance(const std::string & aClassName)
            {
               FactoryBase *  instance_ptr=nullptr;
               const auto iter= FactoryRegistryMap.find(aClassName );
               LOG(INFO)<<"Cantidad de instancias en el mapa: "<<FactoryRegistryMap.size();
               if(iter!=FactoryRegistryMap.end())
               {
                   instance_ptr=(iter->second)();
                   LOG(INFO)<<"Creando la instancia!!!!";
                 }

               //TODO: multiples retornos
               if(instance_ptr!=nullptr)
                 {

                   return std::shared_ptr<FactoryBase > (instance_ptr);
                 }
               else
                 {
                   LOG(INFO)<<"Retornando Puntero Vacio";
                 return nullptr;
                 }
            }

            FactoryBase *   getInstancePtr(const std::string & aClassName)
            {
               FactoryBase *  instance_ptr=nullptr;
               const auto iter= FactoryRegistryMap.find(aClassName );
               LOG(INFO)<<"Cantidad de instancias en el mapa: "<<FactoryRegistryMap.size();
               if(iter!=FactoryRegistryMap.end())
               {
                   instance_ptr=(iter->second)();
                   LOG(INFO)<<"Creando la instancia!!!!";
                 }
                return instance_ptr;

            }
        private:
            KernelFactory()
            {
              LOG(INFO)<<"Creacion de la Factory";
            }
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


}
#endif // GENERIC_FACTORY_H
