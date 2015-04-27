#ifndef GPIO_UTILS_H
#define GPIO_UTILS_H
namespace NSUtils
{
  template<typename addr_type,
  typename reg_type,
  const addr_type addr,
  const reg_type val>
  class reg_access
  {
  public:
  static void reg_set() { /* ... */ }
  static void reg_and() { /* ... */ }
  static void reg_or () { /* ... */ }
  static reg_type reg_get() { /* ... */ }
  static void bit_set() { /* ... */ }
  static void bit_clr() { /* ... */ }
  static void bit_not() { /* ... */ }
  static bool bit_get() { /* ... */ }
  static void variable_reg_set(const reg_type)
  {
  // ...
  }
  };

  template<typename addr_type,
           typename reg_type,
           const addr_type port,
           const reg_type bpos
           >
  class PortPin
  {
    static constexpr addr_type pDir= port - 1U;//Registro Direccion
    static constexpr add_type  pInp= port - 2U;//Data Register
    //definicion de typedef

  };
}
#endif // GPIO_UTILS_H
