#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "InfoFunc.h"
class Parser {
    struct Expression {
        /// <summary>
        /// ����������� ��� �����
        /// </summary>
        /// <param name="token">������ ��������� �� �����</param>
        Expression(std::string token) : token(token) {} 
        /// <summary>
        ///  ����������� ������� ��������
        /// </summary>
        /// <param name="token">��������</param>
        /// <param name="a">�������</param>
        Expression(std::string token, Expression a) : token(token), args{ a } {} 
        /// <summary>
        ///  ����������� �������� ��������
        /// </summary>
        /// <param name="token">��������</param>
        /// <param name="a">����� �������</param>
        /// <param name="b">������ �������</param>
        Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {} 
        /// <summary>
        ///  �������� ��� �����
        /// </summary>
        std::string token; 
        /// <summary>
        ///  ��������� - ��������� ��������
        /// </summary>
        std::vector<Expression> args; 
    };
public:
    /// <summary>
    ///  �����������
    /// </summary>
    /// <param name="input"></param>
    /// <param name="info">���������� � ����������� ��������</param>
    explicit Parser(const char* input, InfoFunc* info) : input(input) { 
        if (info)this->info = info;
        else throw "Info should be not null";
    } // �����������, ��������� ������ � ����������
    /// <summary>
    /// �������� ������� ��������
    /// </summary>
    /// <returns>��������� ����������</returns>
    double parse(); 
private:
    std::string parseToken(); // ������ ���� �����
    Expression parseSimpleExpression(); // ������ ������� ���������
    Expression parseBinaryExpression(int minPriority); // ������ �������� ���������
    InfoFunc* info;
    int getPriority(const std::string& token);
    double eval(const Parser::Expression& e);
    const char* input; // ����� ������, ������� ��� �� ����������
};