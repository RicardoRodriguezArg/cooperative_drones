#ifndef AGENT_GEN_AI_MODEL_INFERENCE_H
#define AGENT_GEN_AI_MODEL_INFERENCE_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include <openvino/genai/chat_history.hpp>
#include <openvino/genai/llm_pipeline.hpp>

namespace butler::agent::inference {

class GenAiModelInference {
public:
    explicit GenAiModelInference(std::unique_ptr<ov::genai::LLMPipeline> pipeline)
        : pipeline_(std::move(pipeline))
        , config_() {
        if (!pipeline_) {
            throw std::invalid_argument("GenAiModelInference requires a valid LLMPipeline instance");
        }
    }

    void set_generation_config(ov::genai::GenerationConfig config) {
        config_ = std::move(config);
    }

    std::string infer(const ov::genai::ChatHistory& history) {
        std::cerr << "[GenAiModelInference] Sending chat history to model\n";

        auto result = pipeline_->generate(history, config_);
        log_metrics(result);
        return result.texts.front();
    }

    std::string infer(std::string_view user_message) {
        std::cerr << "[GenAiModelInference] Input: " << user_message << "\n";

        auto result = pipeline_->generate(std::string(user_message), config_);
        log_metrics(result);
        return result.texts.front();
    }

private:
    void log_metrics(const ov::genai::DecodedResults& result) {
        const auto& m = result.perf_metrics;
        std::cerr << "[GenAiModelInference] Output: " << result.texts.front() << "\n"
                  << "[GenAiModelInference] Tokens in: "   << m.num_input_tokens
                  << "  out: "         << m.num_generated_tokens << "\n"
                  << "[GenAiModelInference] TTFT: "        << m.ttft.mean << " ms"
                  << "  TPOT: "        << m.tpot.mean << " ms/tok"
                  << "  Throughput: "  << m.throughput.mean << " tok/s\n";
    }

    std::unique_ptr<ov::genai::LLMPipeline> pipeline_;
    ov::genai::GenerationConfig             config_;
};

} // namespace butler::agent::inference

#endif // AGENT_GEN_AI_MODEL_INFERENCE_H
