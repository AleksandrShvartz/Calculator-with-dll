#pragma once
#include <string>
#ifdef LN_API_EXPORTS
#define LN_API __declspec(dllexport)
#else
#define LN_API __declspec(dllimport)
#endif
#include <math.h>
/// <summary>
/// Вычисляет логарифм вызывая функцию из библиотечного файла <math.h>
/// </summary>
/// <param name="x">Параметр</param>
/// <returns>Логарифм</returns>
extern "C" LN_API double calculate(double x);
/// <summary>
/// Возвращает строку с названием.
/// </summary>
/// <returns>"ln"</returns>
extern "C" LN_API std::string name();
/// <summary>
/// Возвращает приоритет
/// </summary>
/// <returns>5</returns>
extern "C" LN_API int priority();
