#ifndef
#define
#include "agent/definitions.h"
#include "agent/commands/tree_commands.h"
#include <thread>
#include <queue>

namespace butler::executive
{
	using PriorityQueueType = std::queue<ExecutiveCommandType, 
	                                     std::array<commands::ExecutiveCommandType>,kMaxCommandAllowedPerExecution>,
	                                     std::greater<commands::ExecutiveCommandType>>;

	template<typename CommandRepositoryType>
	class Executive{
	public:
	Executive() = delete;	
	explicit Executive(const CommandRepositoryType & command_repository):command_repository_{command_repository}
	,is_working{false}
	{
		worker_ = std::jthread();
		is_working = true;
	}
	

	~Executive()
	{
		stop();
	}

	void ExecuteCommand(commands::ExecutiveCommandType & command_to_execute)
	{
		std::lock_guard<std::mutext> guard{mutex_};
		commands_to_execute_.enqueue(command_to_execute);
		conditional_variable_.notify_once();
	}

	void stop()
	{
		is_working = false;
	}
	private:

	void worker()
	{
		while(is_working)
		{
			if (conditional_variable_)
			{
				//1.- get the command
				const auto command_to_execute = commands_to_execute_.top();
				commands_to_execute_.pop();

			}
		}
	}


	const CommandRepositoryType & command_repository_;
	std::jthread worker_;
	std::mutex mutex_;
	std::conditional_variable conditional_variable_;
	PriorityQueueType commands_to_execute_{};
	std::atomic_bool is_working{false;}
};
}
#endif
