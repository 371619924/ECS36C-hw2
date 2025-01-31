#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <string>
#include "stack.h"  

bool EvaluatePostfixExpression(const std::string& expression, double& result) {
    Stack stack;
    std::istringstream tokens(expression);
    std::string token;
    int numCount = 0, opCount = 0;
    
    while (tokens >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1) || token.find('.') != std::string::npos) {
            
            try {
                double num = std::stod(token);
                stack.Push(num);
                numCount++;
            } catch (...) {
                std::cerr << "Error: invalid number '" << token << "'\n";
                return false;
            }
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            
            double b, a;
            if (!stack.Peek(b) || !stack.Pop() || !stack.Peek(a) || !stack.Pop()) {
                std::cerr << "Error: invalid expression\n";
                return false;
            }
            
            if (token == "+") stack.Push(a + b);
            else if (token == "-") stack.Push(a - b);
            else if (token == "*") stack.Push(a * b);
            else if (token == "/") {
                if (b == 0) {
                    std::cerr << "Error: division by zero\n";
                    return false;
                }
                stack.Push(a / b);
            }
            opCount++;
        } else {
            std::cerr << "Error: unknown symbol '" << token << "'\n";
            return false;
        }
    }
    
    if (opCount != numCount - 1 || stack.IsEmpty() || !stack.Peek(result)) {
        std::cerr << "Error: invalid expression\n";
        return false;
    }
    return true;
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        double result;
        if (EvaluatePostfixExpression(line, result)) {
            std::cout << std::fixed << std::setprecision(5) << result << "\n";
        } else {
            
            continue;
        }
    }
    std::cout << "Bye!" << std::endl;
    return 0;
}
