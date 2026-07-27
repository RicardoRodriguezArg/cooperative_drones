#ifndef BUTLER_ROBOT_STATE_MOCK_TF_REPORTER_H
#define BUTLER_ROBOT_STATE_MOCK_TF_REPORTER_H

#include "../../../definitions.h"
#include <chrono>
#include <string_view>

namespace butler::robot_state::components {

struct MockTfReporter {
    explicit MockTfReporter(ComponentState state) : state_(state) {}

    [[nodiscard]] ComponentState lookup_transform(
        std::string_view,
        std::string_view,
        std::chrono::milliseconds) const { return state_; }

private:
    const ComponentState state_;
};

} // namespace butler::robot_state::components

#endif // BUTLER_ROBOT_STATE_MOCK_TF_REPORTER_H
