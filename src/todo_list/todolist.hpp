#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace tdlst {
	enum class TaskState : bool 
		{ UNDONE, DONE };
	
	class ToDoList {
	public:
		ToDoList();
		~ToDoList();
		
		int getTasksAmount();
		
		void removeTask(size_t index);
		void addNewTask(std::string newTaskText);
		void editTask(std::string newText, size_t index);
		
		void markAsDone(size_t index);
		void unmarkAsDone(size_t index);
		
		void saveList();
		void loadList();

	private:
		struct Task {
			TaskState state;
			std::string task;
		};
		
		int tasksAmount;
		std::vector<Task> taskList;
		std::filesystem::path dataDirectoryPath;
		
		static constexpr char dataFileName[] = "saved_tasks.tsk";
		static constexpr char dataDirectoryFileName[] = ".task_list_dir";
		
	private:
		bool checkIndexInRange(size_t indexValue);
	};
	
	
} 