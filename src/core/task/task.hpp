#pragma once

#include <string>

namespace tdlst {
	enum class TaskState : bool 
		{ UNDONE, DONE };
	
	struct Task {
		TaskState state;
		std::string taskDescription;
	};
} // namespace tdlst
	