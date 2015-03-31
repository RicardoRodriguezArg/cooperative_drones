/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief:
  *
  */
#ifndef UTILS_TRANSFORM_DATA_H
#define UTILS_TRANSFORM_DATA_H
#include <string>
#include <sstream>
namespace NSUtils
{
  template<typename T>
  static void getValueFromString(T & aValue,const std::string & aStringValue)
  {
      std::stringstream(aStringValue) >> aValue;
  }
}
#endif // UTILS_TRANSFORM_DATA_H
