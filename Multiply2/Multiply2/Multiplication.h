#pragma once
#include <string>
#ifdef MULTIPLACATION_API_EXPORTS
#define MULTIPLACATION_API __declspec(dllexport)
#else
#define MULTIPLACATION_API __declspec(dllimport)
#endif
/// <summary>
///  ������� �������,���������� ������������
/// </summary>
/// <param name="x">������ ��������</param>
/// <param name="y">������ ��������</param>
/// <returns>������������</returns>
extern "C" MULTIPLACATION_API double calculate(double x,double y);
/// <summary>
///  ������ � ������� ������� ����� ������� calculate
/// </summary>
/// <returns>"*"</returns>
extern "C" MULTIPLACATION_API std::string name();
/// <summary>
/// ��������� ��������
/// </summary>
/// <returns>3</returns>
extern "C" MULTIPLACATION_API int priority();


