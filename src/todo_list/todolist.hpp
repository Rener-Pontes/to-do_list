#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace tdlst {
	enum class TaskState : bool 
		{ UNDONE, DONE };
	
	class ToDoList {
	public:
		/**
		 * @brief Construct a new To-Do List object
		 * 
		 * Responsible to instantiate a new object after a few verifications.
		 * It verifies if the application directory exists, if not it'll be created. Also
		 * verifies if the save file exists in the previous directory, if not it'll be
		 * created and the content will be set to 0. If one of these creation operation
		 * fail the method will throw an exception and abort the program.
		 * 
		 * @throw excep::HomePathNotFoundedException	The HOME env variable isn't defined.
		 * @throw excep::FileOpenException    It wasn't possible to create the data file.
		 */
		ToDoList();
		/**
		 * @brief Destroy the To Do List object
		 * 
		 * Responsible to destroy and freeing memory after the object leaves the scope.
		 * Also is responsible to call the saveList method and try save the modifications.
		 * If wasn't possible to finish, a new exception will be thrown and the program
		 * aborted.
		 * 
		 * @throw excep::FileOpenException    Failed attempt to open the data file to save.
		 */
		~ToDoList();
		
		/**
		 * @brief Get the Tasks Amount object.
		 * 
		 * @return The total number of existing tasks.
		 */
		int getTasksAmount() const;
		
		/**
		 * @brief Responsible to remove a specific task.
		 * 
		 * This method receives the task number (the index) and tries to remove it 
		 * from the list if the index is valid, if not it'll catch an exception.
		 * 
		 * @param index A positive integer smaller than the list size.
		 * 
		 * @throw std::out_of_range	    Provided index isn't in range, is a negative
		 * 	      number or a value greater than the taskList vector size.
		 */
		void removeTask(size_t index);
		/**
		 * @brief Responsible to create and append a new task.
		 * 
		 * This method creates a new unmarked task with the provided description, empty or not
		 * and append it to the end of the taskList.
		 * 
		 * @param taskDescription A string describing the task description.
		 */
		void addNewTask(std::string taskDescription);
		/**
		 * @brief Responsible to edit a specific task.
		 * 
		 * This method receives the task number (the index) and tries to edit his description
		 * if the index is valid, if not it'll catch an exception.
		 * 
		 * @param index A positive integer smaller than the list size.
		 * 
		 * @throw std::out_of_range	    Provided index isn't in range, is a negative
		 * 	      number or a value greater than the taskList vector size.
		 */
		void editTask(std::string newText, size_t index);
		
		/**
		 * @brief Responsible to mark as done a specific task.
		 * 
		 * This method receives the task number (the index) and tries to mark it status as DONE
		 * if the index is valid, if not it'll catch an exception.
		 * 
		 * @param index A positive integer smaller than the list size.
		 * 
		 * @throw std::out_of_range	    Provided index isn't in range, is a negative
		 * 	      number or a value greater than the taskList vector size.
		 */
		void markAsDone(size_t index);
		/**
		 * @brief Responsible to mark as undone a specific task.
		 * 
		 * This method receives the task number (the index) and tries to mark it status as UNDONE
		 * if the index is valid, if not it'll catch an exception.
		 * 
		 * @param index A positive integer smaller than the list size.
		 * 
		 * @throw std::out_of_range	    Provided index isn't in range, is a negative
		 * 	      number or a value greater than the taskList vector size.
		 */
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