#pragma warning(disable:4996)
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "Stack_C.h"

int isEmptyStack(struct Stack_C* stack) {
	if (NULL == stack) {
		return 1;
	}
	if (NULL == stack->stack) {
		return 1;
	}
	if (0 == stack->tail) {
		return 1;
	}
	return 0;
}

int initStack(struct Stack_C* stack) {
	stack->tail = 0;
	stack->size = 16;
	stack->stack = (struct CheckerBoard**)malloc(sizeof(struct CheckerBoard*) * 16);
}

void extendStack(struct Stack_C* stack) {
	int cursor = 0;
	int newSize = stack->size;
	newSize = newSize << 1;
	int *newArray = (struct CheckerBoard**)malloc(sizeof(struct CheckerBoard*) * newSize);
	for (; cursor < stack->size; cursor++) {
		// newArray[cursor] = stack->stack[cursor];
		newArray[cursor] = copyCheckerBoard(stack->stack[cursor]);
	}
	free(stack->stack);
	stack->stack = newArray;
	stack->size = newSize;
}

int pushStack(struct Stack_C* stack, struct CheckerBoard* value) {
	if (NULL == stack) {
		return -65535;
	}
	if (NULL == stack->stack) {
		return -65535;
	}
	if (stack->tail == stack->size) {
		extendStack(stack);
	}
	stack->stack[stack->tail++] = value;
	return 1;
}

struct CheckerBoard* popStack(struct Stack_C* stack) {
	if (NULL == stack) {
		return -65535;
	}
	if (NULL == stack->stack) {
		return -65535;
	}
	if (stack->tail < 0 || stack->tail > stack->size) {
		return -65534;
	}
	return stack->stack[--stack->tail];
}

void destroyStack(struct Stack_C* stack) {
	if (NULL == stack) {
		return;
	}
	if (NULL == stack->stack) {
		return;
	}
	else {
		int i = 0;
		for (; i < stack->tail; i++) {
			if (NULL != stack->stack[i]) {
				free(stack->stack[i]);
			}
		}
		free(stack->stack);
	}
}

void displayStack(struct Stack_C* stack) {
	if (NULL == stack) {
		return;
	}
	if (NULL == stack->stack) {
		return;
	}
	if (stack->tail < 0 || stack->tail > stack->size) {
		return;
	}
	printf("\nLength: %d\n", stack->tail);
	int cursor = 0;
	for (; cursor < stack->tail; cursor++) {
		printf("%#X ", stack->stack[cursor]);
	}
	printf("\n");
}

void testStack() {
	struct Stack_C* stack = (struct Stack_C*)malloc(sizeof(struct Stack_C));
	initStack(stack);
	int cursor = 0;
	for (; cursor < 33; cursor++) {
		struct CheckerBoard* checkerBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
		initRandomCheckerBoard(3, 3, checkerBoard);
		printf("%d \n", checkerBoard->height);
		pushStack(stack, checkerBoard);
		displayStack(stack);
		if (cursor == 0) {
			printf("Length: %d\n", stack->tail);
			struct CheckerBoard* temp = popStack(stack);
			printf("Pop: %#X\n", temp);
			free(temp);
			printf("Length: %d\n", stack->tail);
		}
	}
	printf("Pop: %$#X\n", popStack(stack));
	printf("Length: %d\n", stack->tail);
	destroyStack(stack);
	free(stack);
}
