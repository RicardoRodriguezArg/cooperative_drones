#ifndef BUTLER_COMMANDS_HIGH_LEVEL_COMMANDS_H
#define BUTLER_COMMANDS_HIGH_LEVEL_COMMANDS_H

#include <cstdint>


namespace butler::commands {
enum class Priority: std::uint8_t
{
    kLow=0,
    kLevelOne=1
};

enum class Type: std::uint8_t
{
    kStop,
    kMoveTo
};



} // namespace butler::commands


#endif // BUTLER_COMMANDS_HIGH_LEVEL_COMMANDS_H
