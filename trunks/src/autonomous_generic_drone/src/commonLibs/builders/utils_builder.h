#ifndef UTILS_BUILDER_H
#define UTILS_BUILDER_H
#include <iterator>
#include <tuple>
#include "../utils_generics/utils_transform_data.h"
//CLASE AL PEDO!!!
//TODO:Eliminar clase
namespace NSBuilders
{
  namespace Utils
  {
    namespace
    {
      static const unsigned DEFAULT_PROXY_ID=0U;
    }

    template<typename Proxy>
    struct ProxyData
    {
      ProxyData():isSet(false)
      {}

      void clear()
      {
        ProxyID.clear();
        ProxyPtr=nullptr;
        DataType.clear();
        MsgDataType.clear();
        isSet=false;

      }
      bool isSet;
      std::string ProxyID;
      Proxy * ProxyPtr;//Este puntero no es mio
      std::string DataType;
      std::string MsgDataType;

    };
  }
}
#endif // UTILS_BUILDER_H
