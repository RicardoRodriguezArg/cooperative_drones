#ifndef BUTLER_EXECUTIVE_CONFIG_H
#define BUTLER_EXECUTIVE_CONFIG_H

#include "../commands/high_level_commands.h"
#include "../landmarks/landmark_info.h"
#include "../robot_state/state.h"

#include <functional>
#include <string>
#include <vector>

namespace butler::executive {



struct CommandTreeExecutorConfig {
    CommandTreeExecutorConfig() = delete;
    CommandTreeExecutorConfig(
        ValidateLandmarkFn      validate_landmark,
        ValidateArrivalFn       validate_arrival,
        ValidateComponentFn     validate_component,
        ExecuteCommandFn        execute_command,
        CommunicateReturnHomeFn communicate_return_home,
        CommunicateWaitingFn    communicate_waiting,
        CommunicateNotListedFn  communicate_not_listed)
        : validate_landmark(std::move(validate_landmark))
        , validate_arrival(std::move(validate_arrival))
        , validate_component(std::move(validate_component))
        , execute_command(std::move(execute_command))
        , communicate_return_home(std::move(communicate_return_home))
        , communicate_waiting(std::move(communicate_waiting))
        , communicate_not_listed(std::move(communicate_not_listed))
    {}

    const ValidateLandmarkFn      validate_landmark;
    const ValidateArrivalFn       validate_arrival;
    const ValidateComponentFn     validate_component;
    const ExecuteCommandFn        execute_command;
    const CommunicateReturnHomeFn communicate_return_home;
    const CommunicateWaitingFn    communicate_waiting;
    const CommunicateNotListedFn  communicate_not_listed;
};

} // namespace butler::executive

#endif // BUTLER_EXECUTIVE_CONFIG_H
