//
// Created by MagicBook on 2020/10/24.
//

#ifndef AI_SEARCHING_STACK_C_H
#define AI_SEARCHING_STACK_C_H

#include "CheckerBoard.h"

// Stack_C

struct Stack_C {
    int tail;
    int size;
    struct CheckerBoard** stack;
};

int isEmptyStack(struct Stack_C* stack);

struct Stack_C* copyStack(struct Stack_C* stack);

int inStack(struct Stack_C* stack, struct CheckerBoard* checkerBoard);

struct Stack_C* initStack();

void extendStack(struct Stack_C* stack);

int pushStack(struct Stack_C* stack, struct CheckerBoard* checkerBoard);

struct CheckerBoard* popStack(struct Stack_C* stack);

void destroyStack(struct Stack_C* stack);

void destroyStackOnly(struct Stack_C* stack);

void displayStack(struct Stack_C* stack);

void testStack();

#endif //AI_SEARCHING_STACK_C_H
