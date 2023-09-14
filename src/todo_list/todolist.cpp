#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <filesystem>

#include "exceptions.hpp"
#include "todolist.hpp"

namespace fs = std::filesystem;

tdlst::ToDoList::ToDoList(): tasksAmount(0) {
	try {
		const char* home_path = getenv("HOME");
		
		if (not home_path) 
			throw excep::HomePathNotFoundedException("Error: HOME environment variable not found. Please set it before running the program.");
			
		dataDirectoryPath = fs::path(home_path) / dataDirectoryFileName;
		
		if (not fs::exists(dataDirectoryPath)) {
			fs::create_directory(dataDirectoryPath);
			
			std::cout << "The .task_list_dir directory doesn't exists." << std::endl;
			std::cout << "Creating in: " << dataDirectoryPath.parent_path() << std::endl;
		}
		
		fs::path tasksDataPath = dataDirectoryPath / dataFileName;
		if (not fs::exists(tasksDataPath)){
			std::ofstream savedTasksArch;
			
			savedTasksArch.open(tasksDataPath);
			
			std::cout << "The saved_tasks.tsk file doesn't exists." << std::endl;
			if (not savedTasksArch.is_open())
				throw excep::FileOpenException("Error: The file wasn't created. Please, try again.");
			std::cout << "The file was successfully created." << std::endl;
			
			savedTasksArch << 0 << std::endl;
			savedTasksArch.close();
			
			loadList();
		}
	} catch (const std::exception& e) {
		std::cerr << "Error: Construction of To-Do List didn't finish." << std::endl;
		std::cerr << "   -" << e.what() << std::endl;
		
		abort();
	}
}
tdlst::ToDoList::~ToDoList() {
	saveList();
}


int tdlst::ToDoList::getTasksAmount() {
	return tasksAmount;
}

void tdlst::ToDoList::addNewTask(std::string newTaskText) {
	Task newTask = { 
		TaskState::UNDONE, 
		newTaskText 
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
		
		taskList.at(index).task = newText;
		
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
		arch << taskList[i].task << std::endl;
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
		newTask.task = rawInput.substr(2);
		
		taskList.push_back(newTask);
	}
	
	tasksAmount = linesAmount;
	
	arch.close();
}

bool tdlst::ToDoList::checkIndexInRange(size_t indexValue) {
	if (indexValue < 0)
		throw std::out_of_range("Error: Provided index is out of range.");
	if (indexValue >= taskList.size())
		throw std::out_of_range("Error: Provided index is out of range.");
	
	return true;
}

