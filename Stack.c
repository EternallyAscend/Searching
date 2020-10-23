#pragma warning(disable:4996)
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "Stack.h"

int isEmptyStack(struct Stack* stack) {
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

int initStack(struct Stack* stack) {
	stack->tail = 0;
	stack->size = 16;
	stack->stack = (int*)malloc(sizeof(int) * 16);
}

void extendStack(struct Stack* stack) {
	int cursor = 0;
	int newSize = stack->size;
	newSize = newSize << 1;
	int *newArray = (int*)malloc(sizeof(int) * newSize);
	for (; cursor < stack->size; cursor++) {
		newArray[cursor] = stack->stack[cursor];
	}
	free(stack->stack);
	stack->stack = newArray;
	stack->size = newSize;
}

int pushStack(struct Stack* stack, int value) {
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

int popStack(struct Stack* stack) {
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

void destroyStack(struct Stack * stack) {
	if (NULL == stack) {
		return;
	}
	if (NULL == stack->stack) {
		return;
	}
	else {
		free(stack->stack);
	}
}

void displayStack(struct Stack * stack) {
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
		printf("%d ", stack->stack[cursor]);
	}
	printf("\n");
}

void testStack() {
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	initStack(stack);
	int cursor = 0;
	for (; cursor < 33; cursor++) {
		pushStack(stack, cursor);
		displayStack(stack);
		if (cursor == 0) {
			printf("Length: %d\n", stack->tail);
			printf("Pop: %d\n", popStack(stack));
			printf("Length: %d\n", stack->tail);
		}
	}
	printf("Pop: %d\n", popStack(stack));
	printf("Length: %d\n", stack->tail);
	destroyStack(stack);
	free(stack);
}
