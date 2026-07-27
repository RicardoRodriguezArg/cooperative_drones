#ifndef BUTLER_EXECUTIVE_COMMAND_TREE_EXECUTOR_H
#define BUTLER_EXECUTIVE_COMMAND_TREE_EXECUTOR_H

#include "config.h"
#include "nodes/nodes.h"

#include <behaviortree_cpp/bt_factory.h>

#include <deque>
#include <filesystem>
#include <utility>
#include <vector>

namespace butler::executive {


// ─── Executor ─────────────────────────────────────────────────────────────────

class CommandTreeExecutor {
public:
    CommandTreeExecutor(const CommandTreeExecutorConfig     config) {
        registerNodes(config);
        factory_.registerBehaviorTreeFromFile(xml_path);
        blackboard_ = BT::Blackboard::create();
        tree_       = factory_.createTree("AgentCommandExecutorTree", blackboard_);
    }

    // Returns the blackboard so that robot_state::Reporter can write {components} to it.
    [[nodiscard]] BT::Blackboard::Ptr blackboard() const { return blackboard_; }

    void setCommands(std::deque<Command> commands) {
        blackboard_->set("commands", std::move(commands));
    }

    void setLandmarks(std::vector<Landmark> landmarks) {
        blackboard_->set("landmarks", std::move(landmarks));
    }

    // Tick the tree once.
    //   SUCCESS  — command completed
    //   RUNNING  — command in progress
    //   FAILURE  — command failed or queue is empty
    [[nodiscard]] BT::NodeStatus tick() {
        return tree_.tickOnce();
    }

    // Halts all running nodes and resets SequenceWithMemory state.
    // Must be called by the orchestrator after each command cycle ends.
    void reset() {
        tree_.haltTree();
    }

private:
    void registerNodes(const CommandTreeExecutorConfig& cfg) {
        factory_.registerNodeType<GetNextCommandNode>(
            "GetNextCommand");
        factory_.registerNodeType<ClearBoardFromPreviousCommandExecutionNode>(
            "ClearBoardFromPreviousCommandExecution");
        factory_.registerNodeType<ExecuteCommandWithFeedbackNode>(
            "ExecuteCommandWithFeedback", cfg.execute_command);
        factory_.registerNodeType<ValidateLandmarkNode>(
            "ValidateLandmark", cfg.validate_landmark);
        factory_.registerNodeType<ValidateArrivalToLandmarkNode>(
            "ValidateArrivalToLandmark", cfg.validate_arrival);
        factory_.registerNodeType<ValidateComponentNode>(
            "ValidateComponent", cfg.validate_component);
        factory_.registerNodeType<CommunicateReturnHomeNode>(
            "CommunicateReturnHome", cfg.communicate_return_home);
        factory_.registerNodeType<CommunicateWaitingStatusNode>(
            "CommunicateWaitingStatus", cfg.communicate_waiting);
        factory_.registerNodeType<CommunicateCommandWasNotListedNode>(
            "CommunicateCommandWasNotListed", cfg.communicate_not_listed);
    }

    
    BT::Blackboard::Ptr     blackboard_;
    BT::Tree                tree_;
};

} // namespace butler::executive

#endif // BUTLER_EXECUTIVE_COMMAND_TREE_EXECUTOR_H
