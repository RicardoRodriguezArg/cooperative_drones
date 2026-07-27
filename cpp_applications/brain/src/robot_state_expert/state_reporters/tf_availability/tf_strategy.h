#ifndef BUTLER_ROBOT_STATE_TF_STRATEGY_H
#define BUTLER_ROBOT_STATE_TF_STRATEGY_H

#include "../../../definitions.h"
#include <chrono>
#include <string>
#include <utility>

namespace butler::robot_state::components {

// Monitors a TF transform by attempting a lookupTransform between two frames.
// kId: the ComponentId enum value this strategy is bound to at compile time.
template<ComponentId kId, typename ConcreteStrategy>
struct TfStrategy {
    TfStrategy(
        std::string_view          from_frame,
        std::string_view          to_frame,
        ConcreteStrategy          contrete_stragey,
        std::chrono::milliseconds timeout = std::chrono::milliseconds{500})
        : from_(from_frame), to_(to_frame), contrete_stragey_(std::move(contrete_stragey)), timeout_(timeout) {}

    [[nodiscard]] ComponentId id() const { return kId; }

    [[nodiscard]] ComponentState evaluate() const {
        return contrete_stragey_.lookup_transform(from_, to_, timeout_);
    }

private:
    const std::string               from_;
    const std::string               to_;
    const ConcreteStrategy          contrete_stragey_;
    const std::chrono::milliseconds timeout_;
};

} // namespace butler::robot_state::components

#endif // BUTLER_ROBOT_STATE_TF_STRATEGY_H
