#ifndef BUILDERS_PROXY_H
#define BUILDERS_PROXY_H
#include "builders_traits.h"

namespace NSBuilders
{
  namespace{
    constexpr int ERROR_CODE_INDEX=1;
  }
  /**
   *@brief: Esta clase no realiza el parsing del archivo XML sino que toma la clase que encapsula las opciones de
   *otro builder (En este caso de comunicaciones)
   */
  template<class Options,class ...Args>
  class Builders<NSCommonsLibs::BuilderType::ProxyType,Options,Args...> : public IBuilderInterface
  {
  public:
    Builders(Options * const aOptionPtr):OptionsPtr(aOptionPtr)
    {}
    /**
     * @brief buildAll toma el puntero a la estructura que contienen las opciones del builder que realizo el parsing de las opciones de comunicacion
     * @param aErrorCode codigo de error del builder
     */
    void buildAll(int & aErrorCode)
    {
      aErrorCode=std::get<ERROR_CODE_INDEX>(NSCommonsLibs::ERROR_CODES::BUILDER_PROXY_ERROR);
      if(OptionsPtr!=nullptr)
        {

        }
    }
  private:
    Options * const OptionsPtr;
  };
}
#endif // BUILDERS_PROXY_H
