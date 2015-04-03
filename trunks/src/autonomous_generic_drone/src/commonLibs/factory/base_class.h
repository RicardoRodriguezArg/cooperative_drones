#ifndef BASE_CLASS_H
#define BASE_CLASS_H

#include <unordered_map>
namespace KERNEL {
class FactoryBase
{

public:
    virtual ~FactoryBase(){}
        virtual int getID()
        {
            return 0;//base id
        }
};
}
#endif // BASE_CLASS_H
