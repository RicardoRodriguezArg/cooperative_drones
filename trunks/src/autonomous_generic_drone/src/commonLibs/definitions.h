/**
*@author : Ricardo Rodriguez
*@email: aricardorodriguez@hotmail.com
*@date: 12-03-2015
*@brief: Archivo de clases utiles para la administracion de archivos en linux
*
*
*/
#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <tuple>
namespace NSCommonsLibs
{
    enum class BuilderType
    {
       StreamType,
        ProxyType
    };
namespace ERROR_CODES
{
  enum ERROR_INDEX{
    ERROR_CODE_INDEX=1,
    ERROR_STRING_INDEX=0
  };
  static const std::tuple<std::string,int> OK_ERROR_TUPLE("OK_ERROR_CODE",0);
  static const std::tuple<std::string,int> BUILDER_PROXY_ERROR("Options Ptr not Set",-1);
}

}
#endif // DEFINITIONS_H
