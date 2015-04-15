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
#include <string>
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

    /**
      *@brief clase utiliria para ejecutar una funcion en una tupla
      */
    //caso generico
    namespace{
      static const unsigned ZERO_INDEX=0U;
    }
    template<unsigned INDEX, typename CallBack,typename ...Tuple>
    struct tuple_custom_iterator
    {
      void operator()(std::tuple<Tuple...>& tuple, CallBack aCallBackFunction)
      {
        aCallBackFunction(std::get<INDEX>(tuple));
        //lamada recursiva
        tuple_custom_iterator<INDEX-1,CallBack,Tuple...>{}(tuple,aCallBackFunction);
      }
    };
    //caso de salida
    /**
     *@brief caso de salida de la recursion, en este caso llego a cero el indice
     */
    template<typename CallBack,typename ...Tuple>
    struct tuple_custom_iterator<ZERO_INDEX,CallBack,Tuple...>
    {
      void operator()(std::tuple<Tuple...>& tuple, CallBack aCallBackFunction)
      {
        aCallBackFunction(std::get<ZERO_INDEX>(tuple));

      }
    };

    template<typename CallBack, typename ...TupleParams>
     void tuple_iterator(CallBack callback, std::tuple<TupleParams...> tuple)
    {
      tuple_custom_iterator<std::tuple_size<std::tuple<TupleParams...>>::value,CallBack,TupleParams ...> iterator;
      iterator(tuple,callback);
    }

    template<typename tuple_type>
    void clean_tuple(tuple_type & aTupleType)
    {
      aTupleType.clear();
    }



}


#endif // GENERIS_STRUTURES_H
