#include <iostream>    // For input/output operations.
#include <sstream>     // For string stream processing.
#include <cctype>      // For character classification functions (e.g., isdigit).
#include <iomanip>     // For output formatting (fixed, setprecision).
#include <string>      // For std::string.
#include "stack.h"     // For the Stack class used in evaluating expressions.

/*
Detailed Description:
This program evaluates postfix (Reverse Polish Notation) arithmetic expressions.
It reads expressions from standard input, tokenizes each line, and processes each token.
Numeric tokens (including negative and decimal numbers) are pushed onto a stack.
When an operator (+, -, *, /) is encountered, the program pops two operands from the stack,
applies the operator, and pushes the result back onto the stack.
After processing all tokens, the final result is retrieved from the stack and printed
with a fixed precision of 5 decimal places. The program handles error cases such as invalid tokens,
division by zero, or malformed expressions, and outputs corresponding error messages.
The program continues processing input until end-of-file, then prints "Bye!".
*/

// Function: EvaluatePostfixExpression
// Description: Evaluates a postfix expression given as a string and outputs the result via the reference parameter.
// Parameters:
//   - expression: A string containing the postfix expression tokens separated by whitespace.
//   - result: A reference to a double where the computed result will be stored upon successful evaluation.
// Return Value: Returns true if the expression is evaluated successfully; otherwise, returns false in case of an error.
bool EvaluatePostfixExpression(const std::string& expression, double& result) {
    // Create a Stack instance to store double values during evaluation.
    Stack stack;
    
    // Create an input string stream from the expression to split it into tokens.
    std::istringstream tokens(expression);
    std::string token;  // Variable to hold each token.
    
    // Counters to track the number of numeric tokens and operator tokens.
    int numCount = 0;
    int opCount = 0;
    
    // Process each token in the input expression.
    while (tokens >> token) {
        // Check if the token is numeric:
        // A token is considered a number if it starts with a digit, a minus sign (with more than one character),
        // or contains a decimal point.
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1) || token.find('.') != std::string::npos) {
            try {
                // Convert the token to a double using std::stod.
                double num = std::stod(token);
                // Push the numeric value onto the stack.
                stack.Push(num);
                numCount++;  // Increment the numeric token counter.
            } catch (...) {
                // If conversion fails, print an error message and return false.
                std::cerr << "Error: invalid number '" << token << "'\n";
                return false;
            }
        }
        // Check if the token is one of the supported operators: +, -, *, or /.
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            double b, a;  // Variables to hold the two operands.
            // Retrieve and remove the top two numbers from the stack.
            if (!stack.Peek(b) || !stack.Pop() || !stack.Peek(a) || !stack.Pop()) {
                // If there are not enough operands, the expression is invalid.
                std::cerr << "Error: invalid expression\n";
                return false;
            }
            // Process the operator and push the result back onto the stack.
            if (token == "+")
                stack.Push(a + b);
            else if (token == "-")
                stack.Push(a - b);
            else if (token == "*")
                stack.Push(a * b);
            else if (token == "/") {
                // Check for division by zero.
                if (b == 0) {
                    std::cerr << "Error: division by zero\n";
                    return false;
                }
                stack.Push(a / b);
            }
            opCount++;  // Increment the operator token counter.
        }
        // If the token is neither a number nor a valid operator, output an error message.
        else {
            std::cerr << "Error: unknown symbol '" << token << "'\n";
            return false;
        }
    }
    
    // After processing all tokens, verify the expression's validity:
    // In a proper postfix expression, the number of operators should be one less than the number of numbers,
    // and exactly one value (the final result) should remain on the stack.
    if (opCount != numCount - 1 || stack.IsEmpty() || !stack.Peek(result)) {
        std::cerr << "Error: invalid expression\n";
        return false;
    }
    
    // If everything is correct, return true indicating successful evaluation.
    return true;
}

// Main function: Reads input expressions, evaluates them, and prints the results.
int main() {
    std::string line;  // To store each line of input.
    
    // Read each line from standard input until end-of-file.
    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;  // Skip empty lines.
        
        double result;  // Variable to hold the evaluated result.
        // Evaluate the current postfix expression.
        if (EvaluatePostfixExpression(line, result)) {
            // If successful, output the result in fixed-point notation with 5 decimal places.
            std::cout << std::fixed << std::setprecision(5) << result << "\n";
        } else {
            // On error, continue to the next expression.
            continue;
        }
    }
    
    // After all input is processed, print a farewell message.
    std::cout << "Bye!" << std::endl;
    return 0;  // Return 0 to indicate successful termination.
}
