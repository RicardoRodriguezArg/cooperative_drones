#ifndef BUTLER_EXECUTIVE_NODES_VALIDATE_COMPONENT_NODE_H
#define BUTLER_EXECUTIVE_NODES_VALIDATE_COMPONENT_NODE_H

#include "../config.h"

#include <behaviortree_cpp/condition_node.h>

#include <string>
#include <utility>
#include <vector>

namespace butler::executive {

class ValidateComponentNode final : public BT::ConditionNode {
public:
    ValidateComponentNode(const std::string& name,
                          const BT::NodeConfig& config,
                          const ValidateComponentFn fn)
        : BT::ConditionNode(name, config), validate_fn_(fn) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<Command>("command"),
            BT::InputPort<std::vector<Component>>("components"),
        };
    }

private:
    BT::NodeStatus tick() override {
        auto command    = getInput<Command>("command");
        auto components = getInput<std::vector<Component>>("components");
        if (!command || !components)
            return BT::NodeStatus::FAILURE;
        return validate_fn_(*command, *components)
            ? BT::NodeStatus::SUCCESS
            : BT::NodeStatus::FAILURE;
    }

    const ValidateComponentFn validate_fn_;
};

} // namespace butler::executive

#endif // BUTLER_EXECUTIVE_NODES_VALIDATE_COMPONENT_NODE_H
