#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function


int main(int argc, char* argv[]){
	int product = 1;
	for (int i = 1; i < argc; i++){
		int x = atoi(argv[i]);
		product = product*x;

	}
	std::cout << product<<std::endl;

}