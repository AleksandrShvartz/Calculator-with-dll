#include "Parser.h"
std::string Parser::parseToken() {

    // ���� input ���������� � �����, �� ������ �����.
    if (std::isdigit(*input)) {
        std::string number;
        while (std::isdigit(*input) || *input == '.') number.push_back(*input++);
        return number;
    }

    // ������ ���� ��������� ������� - �������� � ������.
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
    return ""; // �����-�� ����������� �����, ��� ������ '\0' - ����� ������.
}
Parser::Expression Parser::parseSimpleExpression() {
    // ������ ������ �����.
    auto token = parseToken();
    if (token.empty()) // ����������� ����� ������, ��� ����������� �����
        throw std::runtime_error("Invalid input");

    if (std::isdigit(token[0])) // ���� ��� �����, ���������� ��������� ��� ����������
        return Expression(token);

    if (token == "(") {
        double result = parse();
        if (parseToken() != ")") throw std::runtime_error("Expected ')'");
        return std::to_string(result); // ���� ��� ������, ������ � ���������� ��������� � �������
    }

    // �����, ��� ������� �������� ("-", "sin", � �.�.)
    auto arg = parseSimpleExpression(); // ������ �� ��������.
    return Expression(token, arg);
}
int Parser::getPriority(const std::string& token) {
    for (int i = 0; i != info->namesTwo.size(); ++i) {
        if (token == info->namesTwo.at(i))
            return info->prioritiesTwo.at(i);
    }    
    return 0; // ���������� 0 ���� ����� - ��� �� �������� �������� (�������� ")")
}
Parser::Expression Parser::parseBinaryExpression(int minPriority) {
    auto leftExpr = parseSimpleExpression(); // ������ ������� ���������.

    for (;;) {
        auto op = parseToken(); // ������� ������� �������� ��������.
        auto priority = getPriority(op);
        // ������� �� ����� ���� �� ��������� ������� ����� (��� ��� �� �������� ��������).
        if (priority <= minPriority) {
            input -= op.size(); // ������ ����� �������,
            return leftExpr; // ���������� ��������� �����.
        }

        // ������ ��������� ������. ������� �������� ������ ����������� ���������.
        auto right_expr = parseBinaryExpression(priority);
        leftExpr = Expression(op, leftExpr, right_expr); // ��������� ��������� �����.
    } // ��������� ����: ������� ��������, � �������� �� ����������.
}
double Parser::parse() {
    const Parser::Expression& e = parseBinaryExpression(0);
    return eval(e);;
}
double Parser::eval(const Parser::Expression& e) {
    switch (e.args.size()) {
    case 2: { // ��� ��������� - �������� ��������.
        auto a = eval(e.args[0]);
        auto b = eval(e.args[1]);
        for (int i = 0; i != info->funcTwo.size(); ++i) {
            if (info->namesTwo.at(i) == e.token) {
                return info->funcTwo.at(i)(a, b);
            }
        }
            
        throw std::runtime_error("Unknown binary operator");
    }

    case 1: { // ���� ��������.
        auto a = eval(e.args[0]);
        for (int i = 0; i != info->funcOne.size(); ++i) {
            if (info->namesOne.at(i) == e.token) {
                return info->funcOne.at(i)(a);
            }
        }
        throw std::runtime_error("Unknown unary operator");
    }

    case 0: { // ����� (���� ����������).
        return strtod(e.token.c_str(), nullptr);
    }
    }

    throw std::runtime_error("Unknown expression type");
}