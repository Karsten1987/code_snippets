#include <stdio.h>
#include <iostream>
#include <vector>

int sum(const std::vector<int> arr ,int  idx){
	if (idx == arr.size()){
		return 0;
	}
	else{
		return arr[idx]+sum(arr, ++idx);
	}
}

std::string swap(const std::string& input)
{
	size_t input_length = input.size();

	std::string output;
	output.resize(input.size());


	std::cerr << "half:" << input_length/2 << std::endl;

	for (size_t i = 0; i < input_length/2; i++)
	{
		output.at(i) = input.at(input_length-1-i);
		output.at(input_length-1-i) = input.at(i);
	}
	if (input_length%2 !=0)
	{
		output.at(input_length/2-1+1) = input.at(input_length/2-1+1);
	}

	return output;
}

int main()
{

	std::vector<int> arr = std::vector<int>(5,1);
	for(int i = 0; i< arr.size(); ++i){
		arr[i] = i+1;
		std::cerr << arr[i] << std::endl;
	}

	int k = sum(arr, 0);
	std::cerr << k << std::endl;


	std::string hallo = "hallo";
	std::string inv_hallo = swap(hallo);

	std::cerr << inv_hallo << std::endl;

	return 0;
}
