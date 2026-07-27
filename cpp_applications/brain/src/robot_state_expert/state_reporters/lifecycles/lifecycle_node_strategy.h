#ifndef BUTLER_ROBOT_STATE_LIFECYCLE_NODE_STRATEGY_H
#define BUTLER_ROBOT_STATE_LIFECYCLE_NODE_STRATEGY_H

#include "../../../definitions.h"
#include <string>
#include <utility>

namespace butler::robot_state::components {

// Monitors a lifecycle-managed ROS2 node by querying its lifecycle state service.
// kId: the ComponentId enum value this strategy is bound to at compile time.
template<ComponentId kId, typename ConcreteStrategy>
struct LifecycleNodeStrategy {
    explicit LifecycleNodeStrategy(std::string_view node_name, ConcreteStrategy contrete_stragey)
        : node_name_(node_name), contrete_stragey_(std::move(contrete_stragey)) {}

    [[nodiscard]] ComponentId id() const { return kId; }

    [[nodiscard]] ComponentState evaluate() const {
        return contrete_stragey_.get_current_state();
    }

private:
    const std::string      node_name_;
    const ConcreteStrategy contrete_stragey_;
};

} // namespace butler::robot_state::components

#endif // BUTLER_ROBOT_STATE_LIFECYCLE_NODE_STRATEGY_H
