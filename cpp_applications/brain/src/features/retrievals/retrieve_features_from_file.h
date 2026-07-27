#ifndef BUTLER_FEATURES_RETRIEVALS_RETRIEVE_FROM_FILE_H
#define BUTLER_FEATURES_RETRIEVALS_RETRIEVE_FROM_FILE_H

#include "/home/operador/Documents/tmp/agent/definitions.h"
#include <expected>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace butler::features::retrievals {

template<typename FeatureFamilyContainerType>
struct RetrieveFeaturesFromFile {
    using FeatureReturnType = std::expected<typename FeatureFamilyContainerType::ReturnType, std::string>;
    using FeatureIdType = typename FeatureFamilyContainerType::FeatureIdType;

    explicit RetrieveFeaturesFromFile(const std::string& input_file)
        : features_map_{LoadFeaturesFromFile(input_file)} {}

    FeatureReturnType get(const butler::features::FeatureType type, const FeatureIdType& id) const {
        const auto it = features_map_.find(type);
        if (it == features_map_.cend())
            return std::unexpected("Feature type not registered");
        return it->second.get(id);
    }

private:
    static std::unordered_map<butler::features::FeatureType, FeatureFamilyContainerType>
    LoadFeaturesFromFile(const std::string& file_name) {
        std::ifstream file{file_name};
        if (!file.is_open())
            throw std::runtime_error{"Cannot open feature file: " + file_name};

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line))
            if (!line.empty())
                lines.push_back(std::move(line));

        auto container = FeatureFamilyContainerType::from_lines(lines);
        return {{FeatureFamilyContainerType::kFeatureKind, std::move(container)}};
    }

    const std::unordered_map<butler::features::FeatureType, FeatureFamilyContainerType> features_map_;
};

} // namespace butler::features::retrievals

#endif // BUTLER_FEATURES_RETRIEVALS_RETRIEVE_FROM_FILE_H
