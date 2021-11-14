#include "pch.h"
#include "Ln.h"
#include "pch.h"

double calculate(double x) {
    return log(x);
}
std::string name()
{
    return "ln";
}

int priority()
{
    return 5;
}
