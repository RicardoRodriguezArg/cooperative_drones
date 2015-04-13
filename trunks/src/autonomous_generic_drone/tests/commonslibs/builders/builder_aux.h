#ifndef CMD_BUILDER_AUX_H
#define CMD_BUILDER_AUX_H
#include <unordered_map>
namespace NSTest
{
  namespace ProxyBuilder
  {
    struct KeyType
    {

    };
    struct ICom
    {

    };
    template<typename KeyType,typename ICommInterface>
    struct BuilderUitlsOption
    {
     // std::unordered_map<KeyType,ICommInterface * const> optionmap;
    };
  }

}
#endif // CMD_BUILDER_AUX_H
