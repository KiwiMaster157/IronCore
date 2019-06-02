#include <iostream>

enum X : short
{
	a, b, c
};

int main()
{
	std::cout << sizeof(void*) << std::endl << sizeof(X) << std::endl;
	
	return 0;
}