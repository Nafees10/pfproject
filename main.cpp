#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "usfml.h"
#include "base.h"

int main(){
	srand(time(NULL)); // set RNG seed to current time
	run();
	return 0;
}
