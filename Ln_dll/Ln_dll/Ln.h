#pragma once
#include <string>
#ifdef LN_API_EXPORTS
#define LN_API __declspec(dllexport)
#else
#define LN_API __declspec(dllimport)
#endif
#include <math.h>
/// <summary>
/// ��������� �������� ������� ������� �� ������������� ����� <math.h>
/// </summary>
/// <param name="x">��������</param>
/// <returns>��������</returns>
extern "C" LN_API double calculate(double x);
/// <summary>
/// ���������� ������ � ���������.
/// </summary>
/// <returns>"ln"</returns>
extern "C" LN_API std::string name();
/// <summary>
/// ���������� ���������
/// </summary>
/// <returns>5</returns>
extern "C" LN_API int priority();
