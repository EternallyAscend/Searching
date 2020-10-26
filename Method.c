//
// Created by MagicBook on 2020/10/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "Method.h"
#include "Stack_C.h"

//struct Method {
//	int depth; // Store current searching depth.
//	int score; // Using it in A or A* Algorithm.
//	int nodeCounter; // Record all reached nodes.
//	struct CheckerBoard *checkerBoard; // Current.
//	struct Stack *method; // History with current.
//};


int isNullMethod(struct Method* method) {
    if (NULL == method) {
        return 1;
    }
    if (NULL == method->stack) {
        free(method);
        return 1;
    }
    return 0;
}

// Init an empty method with completed empty stack.
struct Method* initEmptyMethod() {
    struct Method* method;
    method = (struct Method*)malloc(sizeof(struct Method));
    method->depth = 0;
    method->score = 0;
    method->nodeCounter = 0;
    method->checkerBoard = NULL;
    method->stack = initStack();
    return method;
}

struct Method* copyMethod(struct Method* method) {
    struct Method* copy;
    copy = (struct Method*)malloc(sizeof(struct Method));
    copy->depth = method->depth;
    copy->score = method->score;
    copy->nodeCounter = method->nodeCounter;
    copy->checkerBoard = method->checkerBoard;
    copy->stack = copyStack(method->stack);
    return copy;
}

int destroyMethod(struct Method* method) {
    if (isNullMethod(method)) {
        return 0;
    }
    destroyStackOnly(method->stack);
    free(method);
    return 1;
}

// Compare different method for sort by minHeap. -1 => left < right, 0 => equal, 1 => left > right.
int compareMethod(struct Method* left, struct Method* right) {
    if (isNullMethod(left) || isNullMethod(right)) {
        return -65535;
    }
    if (left->score + left->depth < right->score + right->depth) {
        return -1;
    }
    else if (left->score + left->depth == right->score + right->depth) {
        return 0;
    }
    else if (left->score + left->depth > right->score + right->depth) {
        return 1;
    }
}
