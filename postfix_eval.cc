#include <iostream>
#include <sstream>
#include <cctype>
#include <string>

// 自定义栈实现
class Stack {
private:
    struct Node {
        double value;
        Node* next;
        Node(double val, Node* nxt) : value(val), next(nxt) {}
    };
    Node* top;

public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (!IsEmpty()) {
            Pop();
        }
    }
    
    bool IsEmpty() const {
        return top == nullptr;
    }
    
    void Push(double value) {
        top = new Node(value, top);
    }
    
    bool Pop() {
        if (IsEmpty()) return false;
        Node* temp = top;
        top = top->next;
        delete temp;
        return true;
    }
    
    bool Peek(double& value) const {
        if (IsEmpty()) return false;
        value = top->value;
        return true;
    }
};

bool EvaluatePostfixExpression(const std::string& expression, double& result) {
    Stack stack;
    std::istringstream tokens(expression);
    std::string token;
    int numCount = 0, opCount = 0;
    
    while (tokens >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1) || token.find('.') != std::string::npos) {
            // 处理数字
            try {
                double num = std::stod(token);
                stack.Push(num);
                numCount++;
            } catch (...) {
                std::cerr << "Error: invalid number '" << token << "'\n";
                return false;
            }
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // 处理运算符
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
            std::cout << result << "\n";
        }
    }
    std::cout << "Bye!" << std::endl;
    return 0;
}
