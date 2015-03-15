#include <stdio.h>
#include <iostream>

int main()
{
	// int array with alloc 5
	int* arr = new int[5];
	std::cerr << arr[4] << std::endl;
	std::cerr << arr[5] << std::endl;

	int* p_i;

	int i = 5;
	p_i = &i;
	std::cerr << *p_i << std::endl;
	std::cerr << p_i << std::endl;

	int* p_null = NULL;
	if (p_null == NULL)
	{
		std::cerr << "nullpointer" << std::endl;
	}

	int* delete_arr = new int[5];
	delete_arr[0] = 1;
	delete_arr[1] = 2;
	
	std::cerr << "before delete: " << std::endl
			<< delete_arr[0] << std::endl
			<< delete_arr[1] << std::endl;
	delete delete_arr;	
	std::cerr << "after delete: " << std::endl
			<< delete_arr[0] << std::endl
			<< delete_arr[1] << std::endl;

	int* p_another = 0;	
	delete p_another;

	char* c;
	std::cerr << "size of pointer " << sizeof(c) << std::endl;
	std::cerr << "size of element " << sizeof(*c) << std::endl;

	long* l;
	std::cerr << "size of long p " << sizeof(l) << std::endl;
	std::cerr << "size of long " << sizeof(*l) << std::endl;

}
