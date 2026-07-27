#ifndef BUTLER_ROBOT_STATE_MOCK_TOPIC_REPORTER_H
#define BUTLER_ROBOT_STATE_MOCK_TOPIC_REPORTER_H

#include "../../../definitions.h"
#include <chrono>
#include <string_view>

namespace butler::robot_state::components {

struct MockTopicReporter {
    explicit MockTopicReporter(ComponentState state) : state_(state) {}

    [[nodiscard]] ComponentState has_publisher(
        std::string_view,
        std::chrono::milliseconds) const { return state_; }

private:
    const ComponentState state_;
};

} // namespace butler::robot_state::components

#endif // BUTLER_ROBOT_STATE_MOCK_TOPIC_REPORTER_H
