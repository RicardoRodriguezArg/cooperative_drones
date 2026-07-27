#ifndef BUTLER_UTILS_CONCEPTS_VALIDATORS_H
#define BUTLER_UTILS_CONCEPTS_VALIDATORS_H

#include "definitions.h"

#include <concepts>
#include <type_traits>

namespace butler::concepts {

template<typename F>
concept CheckStrategy =
    std::invocable<F> &&
    std::same_as<std::invoke_result_t<F>, butler::robot_state::ComponentState>;

template<typename T>
concept Watchable = requires(const T& ct, T& t) {
    { ct.id()      } -> std::same_as<butler::robot_state::ComponentId>;
    { t.evaluate() } -> std::same_as<butler::robot_state::ComponentState>;
};

template<typename Reporter>
concept ReporterStateValidator =
    Watchable<Reporter> &&
    std::is_const_v<std::remove_reference_t<Reporter>> &&
    !std::is_same_v<std::remove_cvref_t<Reporter>, std::nullptr_t>;

template<typename E>
concept SentinelEnum =
    std::is_scoped_enum_v<E> &&
    requires { E::_Count; };

} // namespace butler::concepts

#endif // BUTLER_UTILS_CONCEPTS_VALIDATORS_H
