#ifndef FRONTEND_REQUEST_PREPROCESSOR_H
#define FRONTEND_REQUEST_PREPROCESSOR_H

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>

#include <openvino/genai/chat_history.hpp>
#include <openvino/genai/json_container.hpp>

#include "inference/gen_ai_model.h"
#include "settings/inference/model_inference.h"

namespace butler::frontend {

class RequestProcessor {
public:
    RequestProcessor()=delete;
    explicit RequestProcessor(std::unique_ptr<butler::agent::inference::GenAiModelInference> inference,
                              const buttler::settings::inference::Manager& settings_manager)
        : m_inference(std::move(inference))
        , m_system_prompt(load_system_prompt(settings_manager.modelfile_path()))
        , m_history({{{"role", "system"}, {"content", m_system_prompt}}}) {
        std::cerr << "[RequestPreprocessor] System prompt loaded ("
                  << m_system_prompt.size() << " chars)\n";
    }

    std::string process(std::string_view user_text) {
        const std::string payload = build_payload(user_text);
        std::cerr << "[RequestPreprocessor] Payload: " << payload << "\n";

        // m_history se mantiene entre llamadas (no se reconstruye de cero)
        // para que el pipeline pueda reusar el KV-cache del prefijo ya
        // procesado (system prompt + turnos previos) en vez de re-prefillear
        // todo en cada request.
        m_history.push_back({{"role", "user"}, {"content", payload}});
        const std::string response = m_inference->infer(m_history);
        m_history.push_back({{"role", "assistant"}, {"content", response}});

        return response;
    }

private:
    static std::string build_payload(std::string_view user_text) {
        // Se serializa con JsonContainer (no concatenando strings a mano)
        // para que user_text quede correctamente escapado: un input con
        // comillas, backslashes o saltos de linea antes rompia el JSON o
        // inyectaba campos extra.
        const ov::genai::JsonContainer payload({
            {"version", "1.0"},
            {"request_type", "from_user"},
            {"user_message", std::string(user_text)}
        });
        return payload.to_json_string();
    }

    static std::string load_system_prompt(std::string_view modelfile_path) {
        std::ifstream file{std::string(modelfile_path)};
        if (!file)
            throw std::runtime_error(std::string("Cannot open Modelfile: ") + std::string(modelfile_path));

        const std::string content{std::istreambuf_iterator<char>(file), {}};

        const std::string marker_open  = "SYSTEM \"\"\"";
        const std::string marker_close = "\"\"\"";

        const auto start = content.find(marker_open);
        if (start == std::string::npos)
            throw std::runtime_error("SYSTEM prompt not found in Modelfile");

        const auto prompt_start = start + marker_open.size();
        const auto end = content.find(marker_close, prompt_start);
        if (end == std::string::npos)
            throw std::runtime_error("Closing triple-quotes not found in Modelfile");

        auto prompt = content.substr(prompt_start, end - prompt_start);
        if (!prompt.empty() && prompt.front() == '\n') prompt.erase(0, 1);
        if (!prompt.empty() && prompt.back()  == '\n') prompt.pop_back();
        return prompt;
    }

   
    std::unique_ptr<butler::agent::inference::GenAiModelInference> m_inference;
    const std::string                               m_system_prompt;
    ov::genai::ChatHistory                          m_history;
};

} // namespace butler::frontend

#endif // FRONTEND_REQUEST_PREPROCESSOR_H
