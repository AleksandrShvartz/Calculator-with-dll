#pragma once
typedef double(*funcWithOneArg)(double);
typedef double(*funcWithTwoArg)(double, double);
typedef std::string(*funcName)();
typedef int(*funcPriority)();
struct InfoFunc {
	std::vector<funcWithOneArg>funcOne;
	std::vector<funcWithTwoArg>funcTwo;
	std::vector<std::string>namesOne;
	std::vector<std::string>namesTwo;
	std::vector<int>prioritiesTwo;
};