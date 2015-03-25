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
}


#endif // GENERIS_STRUTURES_H
