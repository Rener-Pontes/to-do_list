#pragma once

#include <string>
#include <vector>

#include "../task/task.hpp"


namespace tdlst {
	class ToDoList {
	public:
		/**
		 * @brief Construct a new To Do List object.
		 * 
		 * Construct a new object, setting it name to the provided.
		 * 
		 * @param listName The list name.
		 */
		ToDoList(const std::string& listName);
		/**
		 * @brief Construct a new To Do List object.
		 * 
		 * Construct a new object, setting it name and content to the provided.
		 * 
		 * @param listName 
		 * @param tasksList 
		 */
		ToDoList(const std::string& listName, std::vector<Task>& tasksList);
		
		/**
		 * @brief Returns the number of existing tasks.
		 * 
		 * @return The total number of existing tasks.
		 * @const
		 */
		inline int getTasksAmount() const;
		/**
		 * @brief Returns the current List name.
		 * 
		 * @return The list name.
		 * @const
		 */
		inline std::string getListName() const;
		/**
		 * @brief Returns a constant reference of the list of tasks.
		 * 
		 * @return Constant reference of an vector<Task>.
		 */
		const inline std::vector<Task> getTaskList() const;

		/**
		 * @brief Changes the name of current list.
		 * 
		 * @param newName The new name to be changed
		 */
		inline void changeListName(const std::string& newName);
		
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

		std::string listName;
		std::vector<Task> taskList;
		
	private:
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