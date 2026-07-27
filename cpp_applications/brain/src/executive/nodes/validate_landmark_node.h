#ifndef BUTLER_EXECUTIVE_NODES_VALIDATE_LANDMARK_NODE_H
#define BUTLER_EXECUTIVE_NODES_VALIDATE_LANDMARK_NODE_H

#include "../config.h"

#include <behaviortree_cpp/condition_node.h>

#include <string>
#include <utility>
#include <vector>

namespace butler::executive {

class ValidateLandmarkNode final : public BT::ConditionNode {
public:
    ValidateLandmarkNode(const std::string& name,
                         const BT::NodeConfig& config,
                         const ValidateLandmarkFn fn)
        : BT::ConditionNode(name, config), validate_fn_(fn) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<Command>("command"),
            BT::InputPort<std::vector<Landmark>>("landmarks"),
        };
    }

private:
    BT::NodeStatus tick() override {
        auto command   = getInput<Command>("command");
        auto landmarks = getInput<std::vector<Landmark>>("landmarks");
        if (!command || !landmarks)
            return BT::NodeStatus::FAILURE;
        return validate_fn_(*command, *landmarks)
            ? BT::NodeStatus::SUCCESS
            : BT::NodeStatus::FAILURE;
    }

    const ValidateLandmarkFn validate_fn_;
};

} // namespace butler::executive

#endif // BUTLER_EXECUTIVE_NODES_VALIDATE_LANDMARK_NODE_H
