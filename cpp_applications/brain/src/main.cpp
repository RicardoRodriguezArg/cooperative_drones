#include <iostream>
#include <string>
#include <string_view>

#include "inference/configure.h"
#include "inference/factory.h"
#include "frontend/request_preprocessor.h"
#include "robot_state_expert/builder.h"

int main() {
    static constexpr std::string_view path_to_file{MODEL_INFERENCE_CONFIG_PATH};
    const buttler::settings::inference::Manager settings_manager{path_to_file};

    auto state_reporter = butler::robot_state::Builder{}.state_reporter();

    
    auto model_inference = butler::agent::inference::ModelInferenceFactory::create(settings_manager);
    butler::agent::inference::configure::model(*model_inference, settings_manager);

    butler::frontend::RequestProcessor preprocessor(std::move(model_inference), settings_manager);
//
    //std::cerr << "\nRobot Router ready. Type your command (Ctrl+D to exit):\n\n";
//
    std::string line;
    while (true) {
        std::cerr << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
       std::cout << preprocessor.process(line) << "\n";
    }
//
    //std::cerr << "\nExiting.\n";
    return 0;
}
