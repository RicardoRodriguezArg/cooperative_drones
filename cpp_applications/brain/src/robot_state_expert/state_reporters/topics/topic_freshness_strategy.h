#ifndef BUTLER_ROBOT_STATE_TOPIC_FRESHNESS_STRATEGY_H
#define BUTLER_ROBOT_STATE_TOPIC_FRESHNESS_STRATEGY_H

#include "../../../definitions.h"
#include <chrono>
#include <string>
#include <utility>

namespace butler::robot_state::components {

// Monitors a ROS2 topic by checking whether an active publisher exists within a timeout.
// kId: the ComponentId enum value this strategy is bound to at compile time.
template<ComponentId kId, typename ConcreteStrategy>
struct TopicFreshnessStrategy {
    explicit TopicFreshnessStrategy(
        std::string_view          topic,
        ConcreteStrategy          contrete_stragey,
        std::chrono::milliseconds timeout = std::chrono::milliseconds{1000})
        : topic_(topic), contrete_stragey_(std::move(contrete_stragey)), timeout_(timeout) {}

    [[nodiscard]] ComponentId id() const { return kId; }

    [[nodiscard]] ComponentState evaluate() const {
        return contrete_stragey_.has_publisher(topic_, timeout_);
    }

private:
    const std::string               topic_;
    const ConcreteStrategy          contrete_stragey_;
    const std::chrono::milliseconds timeout_;
};

} // namespace butler::robot_state::components

#endif // BUTLER_ROBOT_STATE_TOPIC_FRESHNESS_STRATEGY_H
