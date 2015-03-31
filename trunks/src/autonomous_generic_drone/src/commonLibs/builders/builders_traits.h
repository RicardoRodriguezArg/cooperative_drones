/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief:
  *
  */
#ifndef BUILDERS_TRAITS_H
#define BUILDERS_TRAITS_H
#include "definitions.h"
namespace NSBuilders
{
    template<NSCommonsLibs::BuilderType>
    class Builders{};
    template<NSCommonsLibs::BuilderType>
    struct BuildersOptions{};
}
#endif // BUILDERS_TRAITS_H
