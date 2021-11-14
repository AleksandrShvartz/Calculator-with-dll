#include "Parser.h"
std::string Parser::parseToken() {

    // Если input начинается с цифры, то парсим число.
    if (std::isdigit(*input)) {
        std::string number;
        while (std::isdigit(*input) || *input == '.') number.push_back(*input++);
        return number;
    }

    // Список всех известных токенов - операции и скобки.
    for (auto& t : info->namesOne) {
        if (std::strncmp(input, t.c_str(), t.size()) == 0) {
            input += t.size();
            return t;
        }
    }
    for (auto& t : info->namesTwo) {
        if (std::strncmp(input, t.c_str(), t.size()) == 0) {
            input += t.size();
            return t;
        }
    }
  /*  if (*input != '\n')
        std::cout << "Error: no suitable operation";*/
    return ""; // Какой-то неизвестный токен, или символ '\0' - конец строки.
}
Parser::Expression Parser::parseSimpleExpression() {
    // Парсим первый токен.
    auto token = parseToken();
    if (token.empty()) // Неожиданный конец строки, или неизвестный токен
        throw std::runtime_error("Invalid input");

    if (std::isdigit(token[0])) // Если это цифра, возвращаем выражение без аргументов
        return Expression(token);

    if (token == "(") {
        double result = parse();
        if (parseToken() != ")") throw std::runtime_error("Expected ')'");
        return std::to_string(result); // Если это скобки, парсим и возвращаем выражение в скобках
    }

    // Иначе, это унарная операция ("-", "sin", и т.п.)
    auto arg = parseSimpleExpression(); // Парсим ее аргумент.
    return Expression(token, arg);
}
int Parser::getPriority(const std::string& token) {
    for (int i = 0; i != info->namesTwo.size(); ++i) {
        if (token == info->namesTwo.at(i))
            return info->prioritiesTwo.at(i);
    }    
    return 0; // Возвращаем 0 если токен - это не бинарная операция (например ")")
}
Parser::Expression Parser::parseBinaryExpression(int minPriority) {
    auto leftExpr = parseSimpleExpression(); // Парсим простое выражение.

    for (;;) {
        auto op = parseToken(); // Пробуем парсить бинарную операцию.
        auto priority = getPriority(op);
        // Выходим из цикла если ее приоритет слишком низок (или это не бинарная операция).
        if (priority <= minPriority) {
            input -= op.size(); // Отдаем токен обратно,
            return leftExpr; // возвращаем выражение слева.
        }

        // Парсим выражение справа. Текущая операция задает минимальный приоритет.
        auto right_expr = parseBinaryExpression(priority);
        leftExpr = Expression(op, leftExpr, right_expr); // Обновляем выражение слева.
    } // Повторяем цикл: парсинг операции, и проверка ее приоритета.
}
double Parser::parse() {
    const Parser::Expression& e = parseBinaryExpression(0);
    return eval(e);;
}
double Parser::eval(const Parser::Expression& e) {
    switch (e.args.size()) {
    case 2: { // Два аргумента - бинарные операции.
        auto a = eval(e.args[0]);
        auto b = eval(e.args[1]);
        for (int i = 0; i != info->funcTwo.size(); ++i) {
            if (info->namesTwo.at(i) == e.token) {
                return info->funcTwo.at(i)(a, b);
            }
        }
            
        throw std::runtime_error("Unknown binary operator");
    }

    case 1: { // Один аргумент.
        auto a = eval(e.args[0]);
        for (int i = 0; i != info->funcOne.size(); ++i) {
            if (info->namesOne.at(i) == e.token) {
                return info->funcOne.at(i)(a);
            }
        }
        throw std::runtime_error("Unknown unary operator");
    }

    case 0: { // Числа (ноль аргументов).
        return strtod(e.token.c_str(), nullptr);
    }
    }

    throw std::runtime_error("Unknown expression type");
}