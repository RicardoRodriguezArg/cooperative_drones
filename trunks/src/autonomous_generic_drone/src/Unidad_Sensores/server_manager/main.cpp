#include "server_manager.h"
#include <iostream>

class T
{
    public:
        using Names = std::tuple<char const*, char const*>;
        template<std::size_t index, typename FisrtType=void>
        static char const* getName()
        {
            static constexpr Names names {"First", "Second"};
            return std::get<index>(names);
        }
};

int main()
{
    std::cout << T::getName<1>() << "\n";
}
