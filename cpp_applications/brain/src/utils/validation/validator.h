#ifndef BUTLER_UTILS_VALIDATION_VALIDATOR_H
#define BUTLER_UTILS_VALIDATION_VALIDATOR_H

#include <stdexcept>
#include <string>

namespace butler::utils::validation {

template<typename... Pairs>
void require_all_set(Pairs&&... fields) {
    ([](const auto& p) {
        if (!p.first.has_value())
            throw std::runtime_error(std::string("not set: '") + std::string(p.second) + "'");
    }(fields), ...);
}

} // namespace butler::utils::validation

#endif // BUTLER_UTILS_VALIDATION_VALIDATOR_H
