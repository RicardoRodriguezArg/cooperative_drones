#ifndef BUTLER_ROBOT_STATE_REPORTER_H
#define BUTLER_ROBOT_STATE_REPORTER_H

#include "../definitions.h"

#include <chrono>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <mutex>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include "utils/concepts/validators.h"
#include "robot_state_expert/compact_state_representation.h"

namespace butler::robot_state {

template<butler::concepts::ReporterStateValidator CustomStateReporter,
         butler::concepts::SentinelEnum           TComponent,
         butler::concepts::SentinelEnum           TState>
class StateReporters {
public:
    constexpr explicit StateReporters(std::initializer_list<CustomStateReporter> entries)
        : entries_(build_map(entries)) {}

    ~StateReporters() { stop(); }

    StateReporters(const StateReporters&)            = delete;
    StateReporters& operator=(const StateReporters&) = delete;
    StateReporters(StateReporters&&)                 = delete;
    StateReporters& operator=(StateReporters&&)      = delete;

    void start() {
        thread_ = std::jthread([this](std::stop_token st) { run(st); });
    }

    void stop() {
        if (thread_.joinable()) {
            thread_.request_stop();
            thread_.join();
        }
    }

private:
    static std::unordered_map<TComponent, CustomStateReporter, EnumHash> build_map(
        std::initializer_list<CustomStateReporter> entries) {
        std::unordered_map<TComponent, CustomStateReporter, EnumHash> map{};
        map.reserve(entries.size());
        for (const auto& e : entries)
            map.emplace(e.id(), e);
        return map;
    }

    void run(std::stop_token token) {
        while (!token.stop_requested())
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    const CompactComponentStateRepresentation<TComponent, TState> state_representation_{};
    const std::unordered_map<TComponent, CustomStateReporter, EnumHash> entries_;
    std::mutex                                         mutex_;
    std::jthread                                       thread_;
};

} // namespace butler::robot_state

#endif // BUTLER_ROBOT_STATE_REPORTER_H
