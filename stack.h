#ifndef STACK_H
#define STACK_H

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

#endif
