#include "modul2.h"

void initStack(StackNode*& top) {
    top = nullptr;
}

bool isStackEmpty(const StackNode* top) {
    return top == nullptr;
}

void clearStack(StackNode*& top) {
    while (top != nullptr) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}