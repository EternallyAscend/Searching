//
// Created by MagicBook on 2020/10/24.
//

#ifndef AI_SEARCHING_METHOD_H
#define AI_SEARCHING_METHOD_H

struct Method {
    int depth; // Store current searching depth.
    int score; // Using it in A or A* Algorithm.
    int nodeCounter; // Record all reached nodes.
    struct CheckerBoard *checkerBoard; // Current.
    struct Stack_C *stack; // History with current.
};

int isNullMethod(struct Method* method);

// Init an empty method with completed empty stack.
struct Method* initEmptyMethod();

struct Method* copyMethod(struct Method* method);

int destroyMethod(struct Method* method);

// Compare different method for sort by minHeap. -1 => left < right, 0 => equal, 1 => left > right.
int compareMethod(struct Method* left, struct Method* right);

#endif //AI_SEARCHING_METHOD_H
