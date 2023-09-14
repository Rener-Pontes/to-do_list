#include <iostream>
#include <cstdlib>
#include <filesystem>
#include "todolist.hpp"

void callSave() {
	
}

int main() {
	tdlst::ToDoList tdl;
	
	tdl.addNewTask("comer banana");
	tdl.addNewTask("Fazer sabonete");
	tdl.addNewTask("Olhar o leite.");
}