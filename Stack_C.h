#pragma once
#ifndef STACK_C_H
#define STACK_C_H

#include "CheckerBoard.h"

struct Stack_C {
	int tail;
	int size;
	struct CheckerBoard** stack;
};

int isEmptyStack(struct Stack_C* stack);

int initStack(struct Stack_C* stack);

void extendStack(struct Stack_C* stack);

int pushStack(struct Stack_C* stack, struct CheckerBoard* checkerBoard);

struct CheckerBoard* popStack(struct Stack_C* stack);

void destroyStack(struct Stack_C* stack);

void displayStack(struct Stack_C* stack);

void testStack();

#endif