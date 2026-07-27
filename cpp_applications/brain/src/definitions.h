#ifndef BUTLER_DEFINITIONS_H
#define BUTLER_DEFINITIONS_H

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>


namespace butler::features{
enum class FeatureType : std::uint8_t {kLandmarks};
}

template<>
struct std::hash<butler::features::FeatureType> {
    std::size_t operator()(butler::features::FeatureType e) const noexcept {
        return std::hash<std::underlying_type_t<butler::features::FeatureType>>{}(
            static_cast<std::underlying_type_t<butler::features::FeatureType>>(e));
    }
};

namespace butler::robot_state {

static constexpr std::uint8_t kMaxCommandAllowedPerExecution{2u};

enum class GeneralState : std::uint8_t { Unknown, kFullyOperational };

enum class ComponentState : std::uint8_t { Unknown, Operational, Failure, _Count };

enum class ComponentId : std::uint8_t {
    amcl_localization_pose,
    amcl_particle_cloud,
    amcl_transform,
    map_server,
    map_occupancy_grid,
    tf_broadcast,
    tf_static_broadcast,
    nav2_planner_server,
    nav2_controller_server,
    nav2_behavior_server,
    nav2_bt_navigator,
    nav2_costmap_global,
    nav2_costmap_local,
    _Count
};

struct EnumHash {
    template<typename E>
    std::size_t operator()(E e) const noexcept {
        return std::hash<std::underlying_type_t<E>>{}(
            static_cast<std::underlying_type_t<E>>(e));
    }
};

}

namespace butler::robot_state::components {

template<butler::robot_state::ComponentId, typename> struct LifecycleNodeStrategy;
template<butler::robot_state::ComponentId, typename> struct TopicFreshnessStrategy;
template<butler::robot_state::ComponentId, typename> struct TfStrategy;

// ── AMCL ─────────────────────────────────────────────────────────────────────
template<typename StrategyType> using AmclLocalizationPose = TopicFreshnessStrategy<ComponentId::amcl_localization_pose, StrategyType>;
template<typename StrategyType> using AmclParticleCloud    = TopicFreshnessStrategy<ComponentId::amcl_particle_cloud, StrategyType>;
template<typename StrategyType> using AmclTransform        = TfStrategy<ComponentId::amcl_transform, StrategyType>;

// ── Map ──────────────────────────────────────────────────────────────────────
template<typename StrategyType> using MapServer        = LifecycleNodeStrategy<ComponentId::map_server, StrategyType>;
template<typename StrategyType> using MapOccupancyGrid = TopicFreshnessStrategy<ComponentId::map_occupancy_grid, StrategyType>;

// ── TF ───────────────────────────────────────────────────────────────────────
template<typename StrategyType> using TfBroadcast       = TfStrategy<ComponentId::tf_broadcast, StrategyType>;
template<typename StrategyType> using TfStaticBroadcast = TfStrategy<ComponentId::tf_static_broadcast, StrategyType>;

// ── Nav2 ─────────────────────────────────────────────────────────────────────
template<typename StrategyType> using Nav2PlannerServer    = LifecycleNodeStrategy<ComponentId::nav2_planner_server, StrategyType>;
template<typename StrategyType> using Nav2ControllerServer = LifecycleNodeStrategy<ComponentId::nav2_controller_server, StrategyType>;
template<typename StrategyType> using Nav2BehaviorServer   = LifecycleNodeStrategy<ComponentId::nav2_behavior_server, StrategyType>;
template<typename StrategyType> using Nav2BtNavigator      = LifecycleNodeStrategy<ComponentId::nav2_bt_navigator, StrategyType>;
template<typename StrategyType> using Nav2CostmapGlobal    = LifecycleNodeStrategy<ComponentId::nav2_costmap_global, StrategyType>;
template<typename StrategyType> using Nav2CostmapLocal     = LifecycleNodeStrategy<ComponentId::nav2_costmap_local, StrategyType>;

} // namespace butler::robot_state::components

#endif // BUTLER_DEFINITIONS_H
