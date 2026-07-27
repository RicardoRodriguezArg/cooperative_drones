#ifndef BUTLER_FEATURES_BUILDER_H
#define BUTLER_FEATURES_BUILDER_H

#include "/home/operador/Documents/tmp/agent/features/manager.h"
#include "/home/operador/Documents/tmp/agent/features/retrievals/retrieve_features_from_file.h"
#include "/home/operador/Documents/tmp/agent/features/landmarks/landmarks_container.h"
#include <string>

namespace butler::features {

struct FeatureManagerBuilder {
    explicit FeatureManagerBuilder(std::string landmarks_file) noexcept
        : landmarks_file_{std::move(landmarks_file)} {}

    Manager<retrievals::RetrieveFeaturesFromFile<landmarks::LandmarksContainer>> build() const {
        return Manager{retrievals::RetrieveFeaturesFromFile<landmarks::LandmarksContainer>{landmarks_file_}};
    }

    const std::string landmarks_file_;
};

} // namespace butler::features

#endif // BUTLER_FEATURES_BUILDER_H
