#ifndef BUTLER_SETTINGS_INFERENCE_MODEL_INFERENCE_SETTINGS_H
#define BUTLER_SETTINGS_INFERENCE_MODEL_INFERENCE_SETTINGS_H

#include <cstddef>
#include <string>

namespace buttler::settings::inference {

struct ModelInferenceSettings {
    std::string model_path;
    std::string device;
    std::string modelfile_path;
    std::size_t max_new_tokens{};
    bool        do_sample{};
    bool        apply_chat_template{};
};

} // namespace buttler::settings::inference

#endif // BUTLER_SETTINGS_INFERENCE_MODEL_INFERENCE_SETTINGS_H
