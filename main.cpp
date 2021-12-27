#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "usfml.h"
#include "base.h"

int main(){
	srand(time(NULL));
	run();
	/*int candy = candyGet(CandyProperty::Red, CandyProperty::Wrapped);
	std::cout << candyCheck(candy, CandyProperty::Red, CandyProperty::Wrapped);
	std::cin.ignore(100, '\n');*/
	return 0;
}
