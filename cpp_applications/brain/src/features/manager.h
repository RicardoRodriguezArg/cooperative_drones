#ifndef BUTLER_FEATURES_MANAGER_H
#define BUTLER_FEATURES_MANAGER_H

#include "/home/operador/Documents/tmp/agent/definitions.h"
#include <string>

namespace butler::features {

template<typename RetrievalStrategy>
struct Manager {
    using FeatureReturnType = typename RetrievalStrategy::FeatureReturnType;

    explicit Manager(RetrievalStrategy strategy) noexcept
        : strategy_{std::move(strategy)} {}

    FeatureReturnType get_feature(FeatureType type, const std::string& id) const {
        return strategy_.get(type, id);
    }

    const RetrievalStrategy strategy_;
};

} // namespace butler::features

#endif // BUTLER_FEATURES_MANAGER_H
