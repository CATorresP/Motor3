#include <string>
#include <iostream>

void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit " << std::endl;
	int tmp;
	std::cin >> tmp;
	exit(-1);
}