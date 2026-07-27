#ifndef BUTLER_EXECUTIVE_NODES_COMMUNICATE_COMMAND_WAS_NOT_LISTED_NODE_H
#define BUTLER_EXECUTIVE_NODES_COMMUNICATE_COMMAND_WAS_NOT_LISTED_NODE_H

#include "../config.h"

#include <behaviortree_cpp/action_node.h>

#include <string>
#include <utility>

namespace butler::executive {

class CommunicateCommandWasNotListedNode final : public BT::SyncActionNode {
public:
    CommunicateCommandWasNotListedNode(const std::string& name,
                                       const BT::NodeConfig& config,
                                       const CommunicateNotListedFn fn)
        : BT::SyncActionNode(name, config), communicate_fn_(fn) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<Command>("command"),
        };
    }

private:
    BT::NodeStatus tick() override {
        const auto command = getInput<Command>("command");
        if (!command)
            return BT::NodeStatus::FAILURE;
        communicate_fn_(*command);
        return BT::NodeStatus::SUCCESS;
    }

    const CommunicateNotListedFn communicate_fn_;
};

} // namespace butler::executive

#endif // BUTLER_EXECUTIVE_NODES_COMMUNICATE_COMMAND_WAS_NOT_LISTED_NODE_H
