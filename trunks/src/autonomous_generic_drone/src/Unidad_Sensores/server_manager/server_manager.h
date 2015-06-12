#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H
#include "../definiciones_sensores.h"
#include "../../commonLibs/factory/base_class.h"
#include "../../commonLibs/factory/factory_register.h"
namespace NSSensoresServeManager
{
    class ServerManager : public KERNEL::FactoryBase
    {
        public:
        virtual int getID()
        {
                return 0;// std::get<ControlDef::ClassID::ID_VALUE>(ControlDef::ClassID::ID_ServerManager);
        }
        private:
    };
}
#endif // SERVER_MANAGER_H
