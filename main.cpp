#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "usfml.h"
#include "base.h"

int main(){
	srand(time(NULL));
	run();
	/*int candy = candyGet(CandyProperty::Red, CandyProperty::HStriped);
	std::cout << candyCheck(candy, CandyProperty::Striped);
	std::cin.ignore(100, '\n');*/
	return 0;
}
