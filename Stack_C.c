//
// Created by MagicBook on 2020/10/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "Stack_C.h"

// Stack_C

//struct Stack_C {
//    int tail;
//    int size;
//    struct CheckerBoard** stack;
//};

int isEmptyStack(struct Stack_C* stack) {
    if (NULL == stack) {
        return 1;
    }
    if (NULL == stack->stack) {
        free(stack);
        return 1;
    }
    return 0;
}

struct Stack_C* copyStack(struct Stack_C* stack) {
    if (isEmptyStack(stack)) {
        return NULL;
    }
    struct Stack_C* copy = (struct Stack_C*)malloc(sizeof(struct Stack_C));
    copy->tail = 0;
    copy->size = stack->size;
    copy->stack = (struct CheckerBoard**)malloc(sizeof(struct CheckerBoard*) * copy->size);
    for (; copy->tail < stack->tail; copy->tail++) {
        copy->stack[copy->tail] = stack->stack[copy->tail];
    }
    return copy;
}

int inStack(struct Stack_C* stack, struct CheckerBoard* checkerBoard) {
    if (isEmptyStack(stack)) {
        return -1;
    }
    int cursor = 0;
    for(; cursor < stack->tail; cursor++) {
        if (1 == checkEqualCheckerBoard(stack->stack[cursor], checkerBoard)) {
            return 1;
        }
    }
    return 0;
}

struct Stack_C* initStack() {
    struct Stack_C* stack = (struct Stack_C*)malloc(sizeof(struct Stack_C));
    stack->tail = 0;
    stack->size = 16;
    stack->stack = (struct CheckerBoard**)malloc(sizeof(struct CheckerBoard*) * 16);
    return stack;
}

void extendStack(struct Stack_C* stack) {
    int cursor = 0;
    int newSize = stack->size;
    newSize = newSize << 1;
    struct CheckerBoard** newArray = (struct CheckerBoard**)malloc(sizeof(struct CheckerBoard*) * newSize);
    for (; cursor < stack->size; cursor++) {
         newArray[cursor] = stack->stack[cursor];
//        newArray[cursor] = copyCheckerBoard(stack->stack[cursor]);
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
        return NULL;
    }
    if (NULL == stack->stack) {
        return NULL;
    }
    if (stack->tail < 0 || stack->tail > stack->size) {
        return NULL;
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
    free(stack);
}

void destroyStackOnly(struct Stack_C* stack) {
    if (NULL == stack) {
        return;
    }
    if (NULL == stack->stack) {
        return;
    }
    free(stack->stack);
    free(stack);
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
        printf("0X%p ", stack->stack[cursor]);
    }
    printf("\n");
}

void testStack() {
    struct Stack_C* stack = initStack();
    int cursor = 0;
    for (; cursor < 33; cursor++) {
        struct CheckerBoard* checkerBoard = initRandomCheckerBoard(3, 3);
        pushStack(stack, checkerBoard);
        displayStack(stack);
        if (cursor == 0) {
            printf("Length: %d\n", stack->tail);
            struct CheckerBoard* temp = popStack(stack);
            printf("Pop: 0X%p\n", temp);
            free(temp);
            printf("Length: %d\n", stack->tail);
        }
    }
    for (cursor = 0; cursor < stack->tail; cursor++) {
        printCheckerBoard(stack->stack[cursor]);
    }
    printf("Pop: 0X%p\n", popStack(stack));
    printf("Length: %d\n", stack->tail);
    destroyStack(stack);
}
