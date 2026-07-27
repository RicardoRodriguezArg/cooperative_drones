#ifndef BUTLER_EXECUTIVE_NODES_CLEAR_BOARD_FROM_PREVIOUS_COMMAND_EXECUTION_NODE_H
#define BUTLER_EXECUTIVE_NODES_CLEAR_BOARD_FROM_PREVIOUS_COMMAND_EXECUTION_NODE_H

#include "../config.h"

#include <behaviortree_cpp/action_node.h>

#include <string>

namespace butler::executive {

class ClearBoardFromPreviousCommandExecutionNode final : public BT::SyncActionNode {
public:
    ClearBoardFromPreviousCommandExecutionNode(const std::string& name, const BT::NodeConfig& config)
        : BT::SyncActionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<Command>("command"),
            BT::BidirectionalPort<std::string>("feedback"),
            BT::BidirectionalPort<std::string>("status"),
            BT::BidirectionalPort<std::string>("error"),
        };
    }

private:
    BT::NodeStatus tick() override {
        setOutput("feedback", std::string{});
        setOutput("status",   std::string{});
        setOutput("error",    std::string{});
        return BT::NodeStatus::SUCCESS;
    }
};

} // namespace butler::executive

#endif // BUTLER_EXECUTIVE_NODES_CLEAR_BOARD_FROM_PREVIOUS_COMMAND_EXECUTION_NODE_H
