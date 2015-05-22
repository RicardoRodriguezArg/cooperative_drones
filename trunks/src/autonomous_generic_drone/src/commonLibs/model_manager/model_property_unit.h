#ifndef MODEL_PROPERTY_UNIT_H
#define MODEL_PROPERTY_UNIT_H
#include "imodel_properties.h"
#include <type_traits>
#include <iostream>
namespace SADI_MODEL {

template<typename Value >
class ModelProperties : public IModelProperties
{
 public:
    constexpr explicit ModelProperties(const Value & aValue):_Value(aValue)
    {

    }
    void getProperty(int & aValue)
    {
       // if (!std::is_same<int, Value>::value) return;
        aValue=_Value;
    }
    void getProperty(unsigned int & aValue)
    {
       // if(!std::is_same<unsigned int, Value>::value) {
       //     return;
       // }
        aValue=_Value;
    }
    void getProperty(float & aValue)
    {
        //if (!std::is_same<float, Value>::value) return;
        aValue=_Value;
    }
    void getProperty(double & aValue)
    {
        //if(!std::is_same<double, Value>::value) return;

        aValue=_Value;
    }
    void getProperty(long & aValue)
    {
       // if (!std::is_same<double, Value>::value) return;

        aValue=_Value;
    }
    void getProperty(std::string & aValue)
    {
      //  if (!std::is_same<std::string, Value>::value) return;

        aValue=_Value;
    }
    void getProperty(bool & aValue)
    {
       aValue =_Value;
    }
  /*  void getProperty(SADI_PROXY::EPROXYSTATE & aValue)
    {
       aValue =_Value;
    }*/
    template<typename T>
    void setValue(const T & aValue)
    {
       if (!std::is_same<T, Value>::value) return;
        _Value=aValue;
    }

private:
    Value _Value;
};
}
#endif // MODEL_PROPERTY_UNIT_H
