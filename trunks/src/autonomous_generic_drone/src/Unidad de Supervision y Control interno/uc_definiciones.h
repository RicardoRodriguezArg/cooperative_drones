#ifndef UC_DEFINICIONES_H
#define UC_DEFINICIONES_H
#include <string>

namespace ControlDef
{
    namespace ERROR_CODE
    {
        constexpr int OK_ERROR_CODE=0;
        //const std::tuple<int,std::string> ERROR_STATE_NOT_CONFIGURATED(-1,"ERROR_STATE_NOT_CONFIGURATED");
    }
    namespace BuilderName
    {
            static const std::string StreamBuilder("StreamBuilder");

    }
    namespace ConfigFile {
    static const std::string CommunicationXmlFile("/home/ricardo/Desktop/debugger/cooperative_drones/trunks/src/autonomous_generic_drone/config/config/generaloptionconfig.xml");

    }
    namespace ClassID
    {
    constexpr int SERVER_MANAGER_ID=1000;
    }
    namespace NSProxy
    {
      static const std::string CMD_TYPE_ID("CMD_ID");
      static const std::string TELEMETRY_TYPE_ID("TELEMETRY_TYPE_ID");
      static const std::string EVENT_TYPE_ID("EVENT_TYPE_ID");
    }
    namespace NSKernel
    {
      static const std::tuple<int,std::string> ID_ProxyManager(1,"ProxyManager");
      static const std::tuple<int,std::string> ID_ServerManager(2,"ServerManager");
      static const std::tuple<int,std::string> ID_CommandProcessor(3,"CommandProcessor");

    }
}

#endif // DEFINICIONES_H
