#ifndef BUTLER_ROBOT_STATE_BUILDER_H
#define BUTLER_ROBOT_STATE_BUILDER_H

#include "../definitions.h"
#include "reporter.h"
#include "state_reporters/lifecycles/lifecycle_node_strategy.h"
#include "state_reporters/lifecycles/mock_node_reporter.h"
#include "state_reporters/tf_availability/tf_strategy.h"
#include "state_reporters/tf_availability/mock_tf_reporter.h"
#include "state_reporters/topics/topic_freshness_strategy.h"
#include "state_reporters/topics/mock_topic_reporter.h"
#include "state_reporters/base_interface_type_erasure.h"

namespace butler::robot_state {

class Builder {
    using NodeMock  = components::MockNodeReporter;
    using TopicMock = components::MockTopicReporter;
    using TfMock    = components::MockTfReporter;

    using Reporters = StateReporters<const ComponentReporter, ComponentId, ComponentState>;

public:
    Builder() = default;

    Reporters state_reporter()
    {
        components::MapServer<NodeMock>            map_server         {"map_server",        NodeMock{ComponentState::Unknown}};
        components::Nav2PlannerServer<NodeMock>    nav2_planner       {"planner_server",    NodeMock{ComponentState::Unknown}};
        components::Nav2ControllerServer<NodeMock> nav2_controller    {"controller_server", NodeMock{ComponentState::Unknown}};
        components::Nav2BehaviorServer<NodeMock>   nav2_behavior      {"behavior_server",   NodeMock{ComponentState::Unknown}};
        components::Nav2BtNavigator<NodeMock>      nav2_bt_navigator  {"bt_navigator",      NodeMock{ComponentState::Unknown}};
        components::Nav2CostmapGlobal<NodeMock>    nav2_costmap_global{"global_costmap",    NodeMock{ComponentState::Unknown}};
        components::Nav2CostmapLocal<NodeMock>     nav2_costmap_local {"local_costmap",     NodeMock{ComponentState::Unknown}};

        components::AmclLocalizationPose<TopicMock> amcl_pose  {"/amcl_pose",     TopicMock{ComponentState::Unknown}};
        components::AmclParticleCloud<TopicMock>    amcl_cloud {"/particle_cloud", TopicMock{ComponentState::Unknown}};
        components::MapOccupancyGrid<TopicMock>     map_grid   {"/map",            TopicMock{ComponentState::Unknown}};

        components::AmclTransform<TfMock>     amcl_tf      {"map",            "odom",  TfMock{ComponentState::Unknown}};
        components::TfBroadcast<TfMock>       tf_broadcast {"map",            "odom",  TfMock{ComponentState::Unknown}};
        components::TfStaticBroadcast<TfMock> tf_static    {"base_footprint", "laser", TfMock{ComponentState::Unknown}};

        return Reporters{{
            ComponentReporter{std::move(map_server)},
            ComponentReporter{std::move(nav2_planner)},
            ComponentReporter{std::move(nav2_controller)},
            ComponentReporter{std::move(nav2_behavior)},
            ComponentReporter{std::move(nav2_bt_navigator)},
            ComponentReporter{std::move(nav2_costmap_global)},
            ComponentReporter{std::move(nav2_costmap_local)},
            ComponentReporter{std::move(amcl_pose)},
            ComponentReporter{std::move(amcl_cloud)},
            ComponentReporter{std::move(map_grid)},
            ComponentReporter{std::move(amcl_tf)},
            ComponentReporter{std::move(tf_broadcast)},
            ComponentReporter{std::move(tf_static)},
        }};
    }
};

} // namespace butler::robot_state

#endif // BUTLER_ROBOT_STATE_BUILDER_H
