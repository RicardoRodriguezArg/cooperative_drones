#ifndef BUTLER_ROBOT_STATE_MOCK_NODE_REPORTER_H
#define BUTLER_ROBOT_STATE_MOCK_NODE_REPORTER_H

#include "../../../definitions.h"

namespace butler::robot_state::components {

struct MockNodeReporter {
    explicit MockNodeReporter(ComponentState state) : state_(state) {}

    [[nodiscard]] ComponentState get_current_state() const { return state_; }

private:
    const ComponentState state_;
};

} // namespace butler::robot_state::components

#endif // BUTLER_ROBOT_STATE_MOCK_NODE_REPORTER_H
