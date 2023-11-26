#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <filesystem>

#include "todolist.hpp"
#include "../exceptions/exceptions.hpp"

namespace fs = std::filesystem;


tdlst::ToDoList::~ToDoList() {

}


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

void tdlst::ToDoList::saveList() {
	std::ofstream arch;
	
	arch.open(dataDirectoryPath / dataFileName);
	
	if (not arch.is_open()) 
		throw excep::FileOpenException("Error: Failed to open the file to save data.");
	
	arch << tasksAmount << std::endl;
	
	for (int i = 0; i < tasksAmount; i++) {
		arch << (taskList[i].state == tdlst::TaskState::DONE ? 'm' : 'u') << " ";
		arch << taskList[i].taskDescription << std::endl;
	}
	
	arch.close();
}
void tdlst::ToDoList::loadList() {
	std::ifstream arch;
	
	arch.open(dataDirectoryPath / dataFileName);
	
	if (not arch.is_open()) 
		throw excep::FileOpenException("Error: Failed to open the file to load data.");
	
	int linesAmount;
	arch >> linesAmount;
	
	for (int i = 0; i < linesAmount; i++) {
		std::string rawInput;
		Task newTask;
		
		getline(arch, rawInput);
		
		newTask.state = rawInput[0] == 'm' ? tdlst::TaskState::DONE : tdlst::TaskState::UNDONE;
		newTask.taskDescription = rawInput.substr(0, 2);
		
		taskList.push_back(newTask);
	}
	
	tasksAmount = linesAmount;
	
	arch.close();
}

bool tdlst::ToDoList::checkIndexInRange(size_t indexValue) {
	if (indexValue < 0)
		throw std::out_of_range("Error: The provided index is a negative value.");
	if (indexValue >= taskList.size())
		throw std::out_of_range("Error: The provided index is greater than the list size.");
	
	return true;
}

