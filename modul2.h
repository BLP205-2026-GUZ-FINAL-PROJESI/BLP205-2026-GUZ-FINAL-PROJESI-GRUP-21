#ifndef MODUL2_H
#define MODUL2_H

#include <string>

struct StackNode {
    std::string islemAciklamasi;
    StackNode* next;
};

void initStack(StackNode*& top);
bool isStackEmpty(const StackNode* top);
void clearStack(StackNode*& top);

#endif