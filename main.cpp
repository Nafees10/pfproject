#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "usfml.h"
#include "base.h"

int main(){
	srand(time(NULL));
	usfmlInit(800, 600, (char*)"Potato Game");
	while (windowIsOpen()){
		Event event;
		eventWait();
		std::cout << "event type is: " << event.type << "\n";
		if (eventGet(event) && event.type == EventType::WindowCloseButtonPress)
			usfmlDestroy();
	}
	std::cin.ignore (1000, '\n');
	return 0;
}
