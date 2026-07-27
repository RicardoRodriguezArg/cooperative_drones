#ifndef BUTLER_EXECUTIVE_NODES_GET_NEXT_COMMAND_NODE_H
#define BUTLER_EXECUTIVE_NODES_GET_NEXT_COMMAND_NODE_H

#include "../config.h"

#include <behaviortree_cpp/action_node.h>

#include <deque>
#include <string>

namespace butler::executive {

class GetNextCommandNode final : public BT::SyncActionNode {
public:
    GetNextCommandNode(const std::string& name, const BT::NodeConfig& config)
        : BT::SyncActionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return {
            BT::BidirectionalPort<std::deque<Command>>("commands"),
            BT::OutputPort<Command>("command"),
            BT::OutputPort<std::string>("command_type"),
        };
    }

private:
    BT::NodeStatus tick() override {
        const auto command_list = getInput<std::deque<Command>>("commands");
        if (!command_list || command_list->empty())
            return BT::NodeStatus::FAILURE;

        const Command next = command_list->front();
        command_list->pop_front();

        setOutput("commands",     *res);
        setOutput("command",      next);
        setOutput("command_type", next.type);
        return BT::NodeStatus::SUCCESS;
    }
};

} // namespace butler::executive

#endif // BUTLER_EXECUTIVE_NODES_GET_NEXT_COMMAND_NODE_H
