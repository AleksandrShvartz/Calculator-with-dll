// Calculator_with_dll.cpp : Defines the entry point for the application.
//

#include "Calculator_with_dll.h"
#include"Calculator.h"
#include <string>
int main()
{
	Calculator calculator;
	std::string input;
	std::cout <<"Print \"exit\" to exit"<< std::endl;
	while (true) {
		std::getline(std::cin, input);
	if (input.compare("exit") == 0)
			break;
		std::cout << calculator.calculate(input);
		std::cout << std::endl;
	}
	return 0;
}
