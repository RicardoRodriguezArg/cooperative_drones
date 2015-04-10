#ifndef UC_DEFINICIONES_H
#define UC_DEFINICIONES_H
#include <string>
namespace ControlDef
{
    namespace ERROR_CODE
    {
        constexpr int OK_ERROR_CODE=0;
    }
    namespace BuilderName
    {
            static const std::string StreamBuilder("StreamBuilder");

    }
    namespace ConfigFile {
    static const std::string CommunicationXmlFile("/home/ricardo/Desktop/proyecto/cooperative_drones/trunks/src/autonomous_generic_drone/config/config/generaloptionconfig.xml");
    }
    namespace ClassID
    {
    constexpr int SERVER_MANAGER_ID=1;
    }
    namespace NSProxy
    {
      static const std::string CMD_TYPE_ID("CMD_ID");
      static const std::string TELEMETRY_TYPE_ID("TELEMETRY_TYPE_ID");
      static const std::string EVENT_TYPE_ID("EVENT_TYPE_ID");
    }
}

#endif // DEFINICIONES_H
