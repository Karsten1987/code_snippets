#include <map>
#include <iostream>
#include <stdio.h>

int main()
{
	std::map<std::string, int> mappy;
	mappy["a"] = 3;
	std::cerr << "a: " << mappy["a"] << std::endl;
	std::cerr << "b: " << mappy["b"] << std::endl;

	return 0;

}
