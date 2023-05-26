#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "line.h"
#include "point.h"


void compute_squares( unsigned int a[],  unsigned int b[], int n)
{
	
	for (int i = 0; i<n; i++)
	{
		*(b+i) = *(a+i) * *(a+i);
		std::cout<<*(b+i)<<std::endl;
	}


}
int main(){
	unsigned int a[2] = {65535,65536};
	
	unsigned int b[2] = {};
	

	compute_squares(a,b,2);

}