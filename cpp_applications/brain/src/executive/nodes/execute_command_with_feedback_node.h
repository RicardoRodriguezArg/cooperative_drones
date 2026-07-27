#ifndef BUTLER_EXECUTIVE_NODES_EXECUTE_COMMAND_WITH_FEEDBACK_NODE_H
#define BUTLER_EXECUTIVE_NODES_EXECUTE_COMMAND_WITH_FEEDBACK_NODE_H

#include "../config.h"

#include <behaviortree_cpp/action_node.h>

#include <string>
#include <utility>

namespace butler::executive {

class ExecuteCommandWithFeedbackNode final : public BT::StatefulActionNode {
public:
    ExecuteCommandWithFeedbackNode(const std::string& name,
                                   const BT::NodeConfig& config,
                                   const ExecuteCommandFn fn)
        : BT::StatefulActionNode(name, config), execute_fn_(fn) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<Command>("command"),
            BT::InputPort<std::string>("phase"),
            BT::OutputPort<std::string>("feedback"),
            BT::OutputPort<std::string>("status"),
            BT::OutputPort<std::string>("error"),
        };
    }

private:
    BT::NodeStatus onStart() override {
        feedback_ = {};
        return onRunning();
    }

    BT::NodeStatus onRunning() override {
        const auto command = getInput<Command>("command");
        const auto phase   = getInput<std::string>("phase");
        if (!command || !phase)
            return BT::NodeStatus::FAILURE;

        const BT::NodeStatus result = execute_fn_(*command, *phase, feedback_);
        setOutput("feedback", feedback_.feedback);
        setOutput("status",   feedback_.status);
        setOutput("error",    feedback_.error);
        return result;
    }

    void onHalted() override { feedback_ = {}; }

    const ExecuteCommandFn execute_fn_;
    CommandWithFeedback feedback_;
};

} // namespace butler::executive

#endif // BUTLER_EXECUTIVE_NODES_EXECUTE_COMMAND_WITH_FEEDBACK_NODE_H
