#ifndef AGENT_INFERENCE_MODEL_LOADER_H
#define AGENT_INFERENCE_MODEL_LOADER_H

#include <filesystem>
#include <string>
#include <utility>

namespace butler::agent {

class ModelLoader {
public:
    ModelLoader(std::filesystem::path model_path, std::string device = "CPU")
        : model_path_(std::move(model_path))
        , device_(std::move(device)) {}

    [[nodiscard]] const std::filesystem::path& model_path() const noexcept {
        return model_path_;
    }

    [[nodiscard]] const std::string& device() const noexcept {
        return device_;
    }

private:
    std::filesystem::path model_path_;
    std::string           device_;
};

} // namespace butler::agent

#endif // AGENT_INFERENCE_MODEL_LOADER_H
