/**
  *@author : Ricardo Rodriguez
  *@email: aricardorodriguez@hotmail.com
  *@date: 12-03-2015
  *@brief: Archivo que contiene diferentes estructuras genericas multiproposito
  *
  *
  */
#ifndef GENERIS_STRUTURES_H
#define GENERIS_STRUTURES_H
#include <tuple>
namespace NSUitlsGenerics
{
  namespace std {
      struct enum_hash
      {
          template <typename T>
          inline
          typename std::enable_if<std::is_enum<T>::value, std::size_t>::type
          operator ()(T const value) const
          {
              return static_cast<std::size_t>(value);
          }
      };

  }
  //base type definition
  template<typename IndexType,typename NodeAtribute, typename ... Args>
  struct GenericMapNode
  {
    constexpr GenericMapNode(const IndexType & aIndex,
                             const NodeAtribute & aNodeAttribute):Index(aIndex)
                                                                ,NodeTuple(std::make_tuple(aNodeAttribute)
    {}
   constexpr IndexType Index;

   constexpr std::tuple<IndexType,NodeAtribute> NodeTuple;
   typedef std::hash<IndexType> Hashfunction;
  };

}
#endif // GENERIS_STRUTURES_H
