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
    template<NSCommonsLibs::BuilderType, class ...Args>
    class Builders{};

    template<NSCommonsLibs::BuilderType>
    struct BuildersOptions{};
    //declaracion de interface de construccion
    class IBuilderInterface
    {
    public:
        ~IBuilderInterface(){}
        virtual void buildAll(int &) =0;
    };
}
#endif // BUILDERS_TRAITS_H
