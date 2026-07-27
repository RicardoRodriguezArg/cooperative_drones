#ifndef BUTLER_LANDMARKS_LANDMARKS_CONTAINER_H
#define BUTLER_LANDMARKS_LANDMARKS_CONTAINER_H

#include "/home/operador/Documents/tmp/agent/features/landmarks/landmark_info.h"
#include <expected>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace butler::features::landmarks {

struct LandmarksContainer {
    using ReturnType = LandmarkInfo;
    using FeatureIdType = std::string;

    static constexpr butler::features::FeatureType kFeatureKind{butler::features::FeatureType::kLandmarks};

    explicit LandmarksContainer(std::unordered_map<std::string, LandmarkInfo> landmarks) noexcept
        : landmarks_{std::move(landmarks)} {}

    std::expected<ReturnType, std::string> get(const FeatureIdType& id) const {
        const auto it = landmarks_.find(id);
        if (it == landmarks_.cend())
            return std::unexpected("Landmark '" + id + "' not found");
        return it->second;
    }

    // Parses lines with format: <name>, <x_pos>, <y_pos>
    static LandmarksContainer from_lines(const std::vector<std::string>& lines) {
        std::unordered_map<std::string, LandmarkInfo> landmarks;
        for (const auto& line : lines) {
            const auto first_comma = line.find(',');
            if (first_comma == std::string::npos) continue;
            const auto second_comma = line.find(',', first_comma + 1);
            if (second_comma == std::string::npos) continue;

            const auto trim = [](std::string_view s) -> std::string {
                const auto start = s.find_first_not_of(" \t\r\n");
                if (start == std::string_view::npos) return {};
                const auto end = s.find_last_not_of(" \t\r\n");
                return std::string{s.substr(start, end - start + 1)};
            };

            try {
                const std::string name = trim(std::string_view{line}.substr(0, first_comma));
                const double x = std::stod(trim(std::string_view{line}.substr(first_comma + 1, second_comma - first_comma - 1)));
                const double y = std::stod(trim(std::string_view{line}.substr(second_comma + 1)));
                landmarks.emplace(name, LandmarkInfo{name, {x, y}});
            } catch (const std::exception&) {
                continue;
            }
        }
        return LandmarksContainer{std::move(landmarks)};
    }

private:
    const std::unordered_map<std::string, LandmarkInfo> landmarks_;
};

} // namespace butler::features::landmarks

#endif // BUTLER_LANDMARKS_LANDMARKS_CONTAINER_H
