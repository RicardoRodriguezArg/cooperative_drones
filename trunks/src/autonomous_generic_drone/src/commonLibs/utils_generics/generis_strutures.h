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
#include <type_traits>
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

namespace NSUtils
{
    struct MsgData
    {
        void setContenidoMensaje(std::string & )
        {}
        size_t getContenidoMensaje() const
        {}
    };
    template<typename tuple_t>
    struct tuple_key_hash : public std::unary_function<tuple_t, std::size_t>
    {
      std::size_t operator()(const tuple_t & aTupleKey) const
      {
          return (std::get<0>( aTupleKey) ^ std::get<1>( aTupleKey));
      }
    };
    template<typename tuple_t>
    struct tuple_key_equal : public std::binary_function<tuple_t, tuple_t, bool>
    {
      bool operator()(const tuple_t& v0, const tuple_t& v1) const
      {
        return (
                std::get<0>(v0) == std::get<0>(v1) &&
                std::get<1>(v0) == std::get<1>(v1)
                );
      }
    };
}


#endif // GENERIS_STRUTURES_H
