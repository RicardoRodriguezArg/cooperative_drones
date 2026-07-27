#ifndef BUTLER_SETTINGS_INFERENCE_MODEL_INFERENCE_H
#define BUTLER_SETTINGS_INFERENCE_MODEL_INFERENCE_H

#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>

#include "utils/parsers/xml_parser.h"
#include "utils/validation/validator.h"

namespace buttler::settings::inference {

struct Manager {
    Manager()=delete;
    explicit Manager(const std::string_view& path_to_settings) {
        load_setting(path_to_settings);
    }


    [[nodiscard]] const std::string& model_path()        const { return model_path_.value();          }
    [[nodiscard]] const std::string& device()            const { return device_.value();               }
    [[nodiscard]] const std::string& modelfile_path()    const { return modelfile_path_.value();       }
    [[nodiscard]] std::size_t        max_new_tokens()    const { return max_new_tokens_.value();       }
    [[nodiscard]] bool               do_sample()         const { return do_sample_.value();            }
    [[nodiscard]] bool               apply_chat_template() const { return apply_chat_template_.value(); }
    
private:


    

    void load_setting(const std::string_view& path_to_settings) {
        const butler::utils::parsers::XmlParser parser{std::filesystem::path{path_to_settings}};

        model_path_          = parser.get_string({"model_inference", "model_path"});
        device_              = parser.get_string({"model_inference", "device"});
        modelfile_path_      = parser.get_string({"model_inference", "modelfile_path"});
        max_new_tokens_      = parser.get_size_t({"model_inference", "generation", "max_new_tokens"});
        do_sample_           = parser.get_bool(  {"model_inference", "generation", "do_sample"});
        apply_chat_template_ = parser.get_bool(  {"model_inference", "generation", "apply_chat_template"});

        validate();
    }

    void validate() const {
        butler::utils::validation::require_all_set(
            std::pair{model_path_,          "model_path"},
            std::pair{device_,              "device"},
            std::pair{modelfile_path_,      "modelfile_path"},
            std::pair{max_new_tokens_,      "max_new_tokens"},
            std::pair{do_sample_,           "do_sample"},
            std::pair{apply_chat_template_, "apply_chat_template"}
        );
    }

    std::optional<std::string> model_path_         {std::nullopt};
    std::optional<std::string> device_             {std::nullopt};
    std::optional<std::string> modelfile_path_     {std::nullopt};
    std::optional<std::size_t> max_new_tokens_     {std::nullopt};
    std::optional<bool>        do_sample_          {std::nullopt};
    std::optional<bool>        apply_chat_template_{std::nullopt};
    
};

} // namespace buttler::settings::inference

#endif // BUTLER_SETTINGS_INFERENCE_MODEL_INFERENCE_H
