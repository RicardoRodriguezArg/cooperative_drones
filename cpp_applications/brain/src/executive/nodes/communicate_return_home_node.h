#ifndef BUTLER_EXECUTIVE_NODES_COMMUNICATE_RETURN_HOME_NODE_H
#define BUTLER_EXECUTIVE_NODES_COMMUNICATE_RETURN_HOME_NODE_H

#include "../config.h"

#include <behaviortree_cpp/action_node.h>

#include <string>
#include <utility>
#include <vector>

namespace butler::executive {

class CommunicateReturnHomeNode final : public BT::SyncActionNode {
public:
    CommunicateReturnHomeNode(const std::string& name,
                              const BT::NodeConfig& config,
                              const CommunicateReturnHomeFn fn)
        : BT::SyncActionNode(name, config), communicate_fn_(fn) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<Command>("command"),
            BT::InputPort<std::vector<Landmark>>("landmarks"),
        };
    }

private:
    BT::NodeStatus tick() override {
        const auto command   = getInput<Command>("command");
        const auto landmarks = getInput<std::vector<Landmark>>("landmarks");
        if (!command || !landmarks)
            return BT::NodeStatus::FAILURE;
        communicate_fn_(*command, *landmarks);
        return BT::NodeStatus::SUCCESS;
    }

    const CommunicateReturnHomeFn communicate_fn_;
};

} // namespace butler::executive

#endif // BUTLER_EXECUTIVE_NODES_COMMUNICATE_RETURN_HOME_NODE_H
