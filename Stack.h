#pragma once
#ifndef STACK_H
#define STACK_H

struct Stack {
	int tail;
	int size;
	int* stack;
};

int isEmptyStack(struct Stack* stack);

int initStack(struct Stack* stack);

void extendStack(struct Stack* stack);

int pushStack(struct Stack* stack, int value);

int popStack(struct Stack* stack);

void destroyStack(struct Stack* stack);

void displayStack(struct Stack* stack);

#endif