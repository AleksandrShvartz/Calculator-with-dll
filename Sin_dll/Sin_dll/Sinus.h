#pragma once
#include <string>
#ifdef SIN_API_EXPORTS
#define SIN_API __declspec(dllexport)
#else
#define SIN_API __declspec(dllimport)
#endif
/// <summary>
///  ������� ����� ������� ������������� ��������� ��������.
/// </summary>
/// <param name="x">��������</param>
/// <returns>sin(x)</returns>
extern "C" SIN_API double calculate(double x);	
/// <summary>
/// ��� �������
/// </summary>
/// <returns>"sin"</returns>
extern "C" SIN_API std::string name();



