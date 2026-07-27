#ifndef AGENT_INFERENCE_FACTORY_H
#define AGENT_INFERENCE_FACTORY_H

#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include <openvino/genai/llm_pipeline.hpp>
#include <openvino/runtime/properties.hpp>

#include "gen_ai_model.h"
#include "settings/inference/model_inference.h"

namespace butler::agent::inference {



class ModelInferenceFactory {
public:
    [[nodiscard]] static std::unique_ptr<GenAiModelInference> create(
        const buttler::settings::inference::Manager& settings) {
        return std::make_unique<GenAiModelInference>(
            create_pipeline(settings.model_path(), settings.device()));
    }

    [[nodiscard]] static std::unique_ptr<ov::genai::LLMPipeline> create_pipeline(
        const std::filesystem::path& model_path,
        const std::string& device) {
        std::cerr << "[ModelInferenceFactory] Loading model: " << model_path
                  << " on device: " << device << "\n";

        // LATENCY explicito: un solo request interactivo por vez, no
        // conviene dejar que el plugin de CPU asuma un escenario de
        // throughput/multi-stream por default.
        // inference_num_threads: el i7-6700 tiene 8 threads logicos como
        // maximo (4 cores fisicos x hyperthreading). Probado en 4 (peor:
        // TTFT +10%, TPOT +60%), 16 (empatado con no fijar nada) y 32
        // (peor: +30% TTFT, overhead de sobre-suscripcion). Se deja en 16
        // por ser neutro, no por ser mejor que el default.
        const ov::AnyMap properties{
            ov::hint::performance_mode(ov::hint::PerformanceMode::LATENCY),
            ov::inference_num_threads(16),
        };

        const auto t0 = std::chrono::steady_clock::now();
        auto pipeline = std::make_unique<ov::genai::LLMPipeline>(model_path, device, properties);
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - t0).count();

        std::cerr << "[ModelInferenceFactory] Model loaded in " << elapsed << " ms\n";
        return pipeline;
    }

};

} // namespace butler::agent::inference

#endif // AGENT_INFERENCE_FACTORY_H
