#ifndef IMODEL_PROPERTIES_H
#define IMODEL_PROPERTIES_H
#include <string>
#include "definiciones.h"
namespace SADI_MODEL{
struct IModelProperties
{
    virtual ~IModelProperties(){}
    virtual void getProperty(int &)=0;
    virtual void getProperty(unsigned int &)=0;
    virtual void getProperty(float &)=0;
    virtual void getProperty(double &)=0;
    virtual void getProperty(long &)=0;
    virtual void getProperty(bool &)=0;
    virtual void getProperty(std::string &)=0;

};
}
#endif // IMODEL_PROPERTIES_H
