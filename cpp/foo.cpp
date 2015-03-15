#include <stdio.h>
#include <iostream>
int main()
{
	int arr[] = {1,2};
	int* p = &arr[0];
	std::cerr << "pointer p " << p << std::endl;
	std::cerr << "deref p " << *p << std::endl;
	
	int& idx2 = arr[1];

	std::cerr << "item2 " << idx2 << std::endl;
	idx2 = 4;
	std::cerr << "item2 in arr " << arr[1] << std::endl;

	*(p+1) = 20;
	std::cerr << "item2 in arr now " << arr[1] << std::endl;

	*(p+2) = 30;
	std::cerr << "item3 in arr now " << arr[2] << std::endl;

	std::cerr << "item10 in arr now " << arr[10] << std::endl;
	return 0;
}
