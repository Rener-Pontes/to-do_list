#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "../task/task.hpp"


namespace tdlst {
	class ToDoList {
	public:
		ToDoList(std::string& listName);
		ToDoList(std::string& listName, std::vector<Task>& tasksList);
		
		~ToDoList();
		
		/**
		 * @brief Returns the number of existing tasks.
		 * 
		 * @return The total number of existing tasks.
		 * @const
		 */
		int getTasksAmount() const;
		
		/**
		 * @brief Remove/delete the specified task from the list.
		 * 
		 * This method receives the task index (starting from 0) and tries to remove it 
		 * from the list if the index is valid, if not it'll catch an exception.
		 * 
		 * @param index A positive integer smaller than the list size.
		 * 
		 * @throw std::out_of_range	    Provided index isn't in range, is a negative
		 * 	      number or a value greater than the taskList vector size.
		 */
		void removeTask(size_t index);
		/**
		 * @brief Creates a new task in the end of list.
		 * 
		 * This method creates a new unmarked task with the provided description, empty or not,
		 * and append it to the end of the taskList.
		 * 
		 * @param taskDescription A string describing the task description.
		 */
		void addNewTask(std::string taskDescription);
		/**
		 * @brief Edit the description text of the specified task.
		 * 
		 * This method receives the task index (starting from 0) and tries to edit his 
		 * description. If the provided index isn't valid it'll catch an exception.
		 * 
		 * @param index An integer value, greater or equal to 0 and smaller than the list size.
		 * 
		 * @throw std::out_of_range	    Provided index isn't in range, is a negative
		 * 	      number or a value greater than the taskList vector size.
		 */
		void editTask(std::string newText, size_t index);
		
		/**
		 * @brief Mark the specified task as completed (DONE).
		 * 
		 * This method receives the task index (starting from 0) and tries to mark the correspondent
		 * status as DONE. If the provided index isn't valid it'll catch an exception.
		 * 
		 * @param index An integer value, greater or equal to 0 and smaller than the list size.
		 * 
		 * @throw std::out_of_range	    Provided index isn't in range, is a negative
		 * 	      number or a value greater than the taskList vector size.
		 */
		void markAsDone(size_t index);
		/**
		 * @brief Unmark the specified task.
		 * 
		 * This method receives the task index and tries to mark the correspondent status
		 * as UNDONE. If the provided index isn't valid it'll catch an exception.
		 * 
		 * @param index An integer value, greater or equal to 0 and smaller than the list size.
		 * 
		 * @throw std::out_of_range	    Provided index isn't in range, is a negative
		 * 	      number or a value greater than the taskList vector size.
		 */
		void unmarkAsDone(size_t index);

	private:
		int tasksAmount;

		std::vector<Task> taskList;
		std::filesystem::path dataDirectoryPath;
		
		static constexpr char dataFileName[] = "saved_tasks.tsk";
		static constexpr char dataDirectoryFileName[] = ".task_list_dir";
		
	private:
		/**
		 * @brief Saves the list content into a file.
		 * 
		 * Saves the list content into a file for data persistent purposes. Only will be called when
		 * the object is fred naturally.
		 * 
		 * @throw excep::FileOpenException    File opening attempt failed.
		 */
		void saveList();
		/**
		 * @brief Reads file data and load it.
		 * 
		 * Reads the data file content and tries to create all necessary tasks. Used to initiate the 
		 * object. Only will be called in the object constructor.
		 * 
		 * @throw excep::FileOpenException    File opening attempt failed.
		 */
		void loadList();

		/**
		 * @brief Checks if the provided index is valid or not.
		 * 
		 * Do some verification of the received index value, checking if is in the correct range. If
		 * isn't valid, a new exception will be thrown.
		 * 
		 * @param indexValue An integer value, greater or equal to 0 and smaller than the list size.
		 * 
		 * @throw std::out_of_range    Provided index isn't in range, is a negative
		 * 	      number or a value greater than the taskList vector size.
		 */
		bool checkIndexInRange(size_t indexValue);
	};
	
	
} 