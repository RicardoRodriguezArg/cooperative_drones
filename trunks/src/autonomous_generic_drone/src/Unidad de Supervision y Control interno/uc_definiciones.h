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

    namespace ClassID
    {
    constexpr int SERVER_MANAGER_ID=1;
    }
}

#endif // DEFINICIONES_H
