#ifndef AGENT_INFERENCE_BUILDER_H
#define AGENT_INFERENCE_BUILDER_H

#include <cstddef>
#include <filesystem>
#include <memory>
#include <string_view>
#include <string>
#include <utility>

#include "factory.h"
#include "utils/parsers/xml_parser.h"

namespace butler::agent::inference::configure {


    inline void model(GenAiModelInference& model,
                      const buttler::settings::inference::Manager& settings) {
        ov::genai::GenerationConfig config{};
        config.max_new_tokens      = settings.max_new_tokens();
        config.do_sample           = settings.do_sample();
        config.apply_chat_template = settings.apply_chat_template();

        model.set_generation_config(std::move(config));
    }

} // namespace butler::agent::inference

#endif // AGENT_INFERENCE_BUILDER_H
