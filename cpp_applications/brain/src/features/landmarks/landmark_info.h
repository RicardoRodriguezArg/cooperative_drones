#ifndef BUTLER_LANDMARKS_LANDMARK_INFO_H
#define BUTLER_LANDMARKS_LANDMARK_INFO_H

#include "/home/operador/Documents/tmp/agent/definitions.h"
#include <string>
#include <tuple>

namespace butler::features::landmarks {

struct LandmarkInfo {
    LandmarkInfo() = delete;

    explicit LandmarkInfo(std::string id, std::tuple<double, double> position) noexcept
        : id_{std::move(id)}, position_{std::move(position)} {}

    static constexpr butler::features::FeatureType kFeatureKind{butler::features::FeatureType::kLandmarks};
    const std::string id_;
    const std::tuple<double, double> position_;
};

} // namespace butler::features::landmarks

#endif // BUTLER_LANDMARKS_LANDMARK_INFO_H
