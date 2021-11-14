#pragma once
#include <string>
#ifdef SIN_API_EXPORTS
#define SIN_API __declspec(dllexport)
#else
#define SIN_API __declspec(dllimport)
#endif
/// <summary>
///  Считает синус методом аппроксимации табличных значений.
/// </summary>
/// <param name="x">Аргумент</param>
/// <returns>sin(x)</returns>
extern "C" SIN_API double calculate(double x);	
/// <summary>
/// Имя функции
/// </summary>
/// <returns>"sin"</returns>
extern "C" SIN_API std::string name();



