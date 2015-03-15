#include <stdio.h>
#include <iostream>
int main()
{
	int k = 10;
	for(int i = 0; i<k; ++i)
	{
		int m = i%2;
		if (m ==0)
		{
			std::cerr << i << " is even" << std::endl;
		}
	}	
	return 0; 
}
