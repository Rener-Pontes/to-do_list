#include <string>
#include <vector>
#include <iostream>

#include "todolist.hpp"
#include "../task/task.hpp"
#include "../exceptions/exceptions.hpp"


tdlst::ToDoList::ToDoList(const std::string& listName): 
	listName(listName),
	tasksAmount(0) 
	{}

tdlst::ToDoList::ToDoList(const std::string& listName, std::vector<Task>& tasksList): 
	listName(listName), 
	taskList(tasksList),
	tasksAmount(tasksList.size()) 
	{}

int tdlst::ToDoList::getTasksAmount() const {
	return tasksAmount;
}

void tdlst::ToDoList::addNewTask(std::string taskDescription) {
	Task newTask = { 
		TaskState::UNDONE, 
		taskDescription 
	};
	
	taskList.push_back(newTask);
	tasksAmount++;
	
	std::cout << "New task created successfully." << std::endl;
}
void tdlst::ToDoList::removeTask(size_t index) {
	try {
		checkIndexInRange(index);
		
		taskList.erase(taskList.begin() + index);
		tasksAmount--;
		
		std::cout << "Task removed successfully." << std::endl;
		
	}catch (const std::exception& e) {
		std::cerr << "Error: On method call removeTask:" << std::endl;
		std::cerr << "   -" << e.what() << std::endl;
	}
}
void tdlst::ToDoList::editTask(std::string newText, size_t index) {
	try {
		checkIndexInRange(index);
		
		taskList.at(index).taskDescription = newText;
		
		std::cout << "Task edited successfully." << std::endl;
		
	}catch (const std::exception& e) {
		std::cerr << "Error: On method call editTask:" << std::endl;
		std::cerr << "   -" << e.what() << std::endl;
	}
}

void tdlst::ToDoList::markAsDone(size_t index) {
	try {
		checkIndexInRange(index);
		
		taskList.at(index).state = tdlst::TaskState::DONE;
		
		std::cout << "Task marked successfully." << std::endl;
		
	}catch (const std::exception& e) {
		std::cerr << "Error: On method call markAsDone:" << std::endl;
		std::cerr << "   -" << e.what() << std::endl;
	}
}
void tdlst::ToDoList::unmarkAsDone(size_t index) {
	try {
		checkIndexInRange(index);
		
		taskList.at(index).state = tdlst::TaskState::UNDONE;
		
		std::cout << "Task unmarked successfully." << std::endl;
		
	}catch (const std::exception& e) {
		std::cerr << "Error: On method call unmarkAsDone:" << std::endl;
		std::cerr << "   -" << e.what() << std::endl;
	}
}

bool tdlst::ToDoList::checkIndexInRange(size_t indexValue) {
	if (indexValue < 0)
		throw std::out_of_range("Error: The provided index is a negative value.");
	if (indexValue >= taskList.size())
		throw std::out_of_range("Error: The provided index is greater than the list size.");
	
	return true;
}

