#include <iostream>
#include "usfml.h"

int main(){
	createWindow(800, 600, (char*)"potato");
	std::cin.ignore(1000, '\n');
	destroyWindow();
	return 0;
}
