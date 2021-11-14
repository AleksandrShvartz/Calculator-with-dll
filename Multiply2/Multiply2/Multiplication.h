#pragma once
#include <string>
#ifdef MULTIPLACATION_API_EXPORTS
#define MULTIPLACATION_API __declspec(dllexport)
#else
#define MULTIPLACATION_API __declspec(dllimport)
#endif
/// <summary>
///  снавная функция,возвращает произведение
/// </summary>
/// <param name="x">Первый параметр</param>
/// <param name="y">Втррой параметр</param>
/// <returns>Произведение</returns>
extern "C" MULTIPLACATION_API double calculate(double x,double y);
/// <summary>
///  Строка с помощью которой можно вызвать calculate
/// </summary>
/// <returns>"*"</returns>
extern "C" MULTIPLACATION_API std::string name();
/// <summary>
/// Приоритет операции
/// </summary>
/// <returns>3</returns>
extern "C" MULTIPLACATION_API int priority();


