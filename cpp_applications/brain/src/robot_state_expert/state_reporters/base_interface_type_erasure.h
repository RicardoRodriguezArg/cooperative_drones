#ifndef BUTLER_ROBOT_STATE_BASE_INTERFACE_TYPE_ERASURE_H
#define BUTLER_ROBOT_STATE_BASE_INTERFACE_TYPE_ERASURE_H

#include "../../definitions.h"
#include <functional>

namespace butler::robot_state {

// Bridges any Watchable strategy into a uniform type for StateReporters.
// Owns the strategy by value — the strategy (and its mock) live inside this object.
// Base on Type Erasure idiom

struct ComponentReporter {
    template<typename Strategy>
    explicit ComponentReporter(Strategy strategy)
        : id_    (strategy.id())
        , eval_fn_([s = std::move(strategy)] { return s.evaluate(); }) {}

    [[nodiscard]] ComponentId    id()       const { return id_; }
    [[nodiscard]] ComponentState evaluate() const { return eval_fn_(); }

private:
    const ComponentId                     id_;
    const std::function<ComponentState()> eval_fn_;
};

} // namespace butler::robot_state

#endif // BUTLER_ROBOT_STATE_BASE_INTERFACE_TYPE_ERASURE_H
