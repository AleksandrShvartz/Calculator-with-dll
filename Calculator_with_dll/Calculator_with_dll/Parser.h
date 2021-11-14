#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "InfoFunc.h"
class Parser {
    struct Expression {
        /// <summary>
        /// Конструктор для чисел
        /// </summary>
        /// <param name="token">Строка состоящая из числа</param>
        Expression(std::string token) : token(token) {} 
        /// <summary>
        ///  Конструктор унарных операций
        /// </summary>
        /// <param name="token">Операция</param>
        /// <param name="a">Операнд</param>
        Expression(std::string token, Expression a) : token(token), args{ a } {} 
        /// <summary>
        ///  Конструктор бинарных операций
        /// </summary>
        /// <param name="token">Операция</param>
        /// <param name="a">Левый операнд</param>
        /// <param name="b">Правый операнд</param>
        Expression(std::string token, Expression a, Expression b) : token(token), args{ a, b } {} 
        /// <summary>
        ///  Операция или число
        /// </summary>
        std::string token; 
        /// <summary>
        ///  Выражения - аргументы операции
        /// </summary>
        std::vector<Expression> args; 
    };
public:
    /// <summary>
    ///  Конструктор
    /// </summary>
    /// <param name="input"></param>
    /// <param name="info">Информация о загружынных функциях</param>
    explicit Parser(const char* input, InfoFunc* info) : input(input) { 
        if (info)this->info = info;
        else throw "Info should be not null";
    } // Конструктор, принимает строку с выражением
    /// <summary>
    /// Основная функция парсинга
    /// </summary>
    /// <returns>Результат вычисления</returns>
    double parse(); 
private:
    std::string parseToken(); // Парсит один токен
    Expression parseSimpleExpression(); // Парсит простое выражение
    Expression parseBinaryExpression(int minPriority); // Парсит бинарное выражение
    InfoFunc* info;
    int getPriority(const std::string& token);
    double eval(const Parser::Expression& e);
    const char* input; // Кусок строки, который еще не распарсили
};