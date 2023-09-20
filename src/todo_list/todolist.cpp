#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <filesystem>

#include "todolist.hpp"
#include "../exceptions/exceptions.hpp"

namespace fs = std::filesystem;

tdlst::ToDoList::ToDoList(): tasksAmount(0) {
	try {
		const char* home_path = getenv("HOME");
		
		// Checks if the $HOME environment exists
		if (not home_path) 
			throw excep::HomePathNotFoundedException("Error: HOME environment variable not found. Please set it before running the program.");
			
		dataDirectoryPath = fs::path(home_path) / dataDirectoryFileName; // Concat of home_path with directory name
		
		// Check if the data directory already exits
		if (not fs::exists(dataDirectoryPath)) {
			fs::create_directory(dataDirectoryPath);
			
			std::cout << "The .task_list_dir directory doesn't exists." << std::endl;
			std::cout << "Creating in: " << dataDirectoryPath.parent_path() << std::endl;

			// Verify if the directory was created successfully.
			if (not fs::exists(dataDirectoryPath))
				throw excep::BaseDirectoryCreationException("Error: It was not possible to create the necessary directory. Try again later or create it manually.");
			
			std::cout << "Directory created successfully." << std::endl;
		}
		
		fs::path tasksDataPath = dataDirectoryPath / dataFileName; // Concat the directory_path with file name
		// Check if the file exist
		if (not fs::exists(tasksDataPath)){
			std::ofstream savedTasksArch;
			
			savedTasksArch.open(tasksDataPath);
			
			std::cout << "The saved_tasks.tsk file doesn't exists." << std::endl;
			if (not savedTasksArch.is_open()) // Verify if the file was created.
				throw excep::FileCreationException("Error: The file wasn't created. Please, try again.");
			std::cout << "The file was successfully created." << std::endl;
			
			savedTasksArch << 0 << std::endl;
			savedTasksArch.close();			
		}

 		loadList();
	} catch (const std::exception& e) {
		std::cerr << "Error: Construction of To-Do List didn't finish." << std::endl;
		std::cerr << "   -" << e.what() << std::endl;
		
		abort();
	}
}
tdlst::ToDoList::~ToDoList() {
	try {
		saveList();
	} catch (const std::exception& e) {
		std::cerr << "Error: Save of To-Do List couldn't finish." << std::endl;
		std::cerr << "   -" << e.what() << std::endl;

		abort();
	}
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

