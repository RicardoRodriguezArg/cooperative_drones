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
}

#endif // DEFINICIONES_H
