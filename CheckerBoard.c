//
// Created by MagicBook on 2020/10/24.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "CheckerBoard.h"

unsigned long long int b = 0;
unsigned long long int dfs = 0;
unsigned long long int bfs = 0;
unsigned long long int a = 0;
unsigned long long int aStar = 0;

//struct CheckerBoard {
//	int length; // Length of the checkerboard.
//	int height; // Height of the checkerboard.
//	int *checkerBoard; // Store number position.
//	int zeroPosition; // Store where is empty.
//	int lastModified; // Store which moved before.
//};

// If checkerBoard->checkerBoard is NULL, it will free the checkerBoard.
int checkNullCheckerBoard(struct CheckerBoard* checkerBoard) {
    // 1 means null.
    // 0 means not null.
    if (NULL == checkerBoard) {
        return 1;
    }
    if (NULL == checkerBoard->checkerBoard) {
        free(checkerBoard);
        return 1;
    }
    return 0;
}

// Destroy the checkerBoard and the pointer.
void destroyCheckerBoard(struct CheckerBoard* checkerBoard) {
    if (checkNullCheckerBoard(checkerBoard)) {
        return;
    }
    free(checkerBoard->checkerBoard);
    free(checkerBoard);
}

struct CheckerBoard* copyCheckerBoard(struct CheckerBoard* checkerBoard) {
    struct CheckerBoard* copy = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
    copy->height = checkerBoard->height;
    copy->length = checkerBoard->length;
    copy->lastModified = checkerBoard->lastModified;
    copy->zeroPosition = checkerBoard->zeroPosition;
    copy->checkerBoard = (int*)malloc(sizeof(int) * copy->height * copy->length);
    int cursor = 0;
    for (; cursor < copy->height * copy->length; cursor++) {
        copy->checkerBoard[cursor] = checkerBoard->checkerBoard[cursor];
    }
    return copy;
}

// Find position of empty block. Wrong input => -1;
int searchZeroInCheckerBoard(struct CheckerBoard* checkerBoard) {
    if (checkNullCheckerBoard(checkerBoard)) {
        return -1;
    }
    int item = 0;
    for (; item < checkerBoard->length * checkerBoard->height; item++) {
        if (checkerBoard->checkerBoard[item] == 0) {
            checkerBoard->zeroPosition = item;
            return item;
        }
    }
}

// Init new empty checkerBoard with `struct CheckerBoard* = initCheckerBoard(length, height);`
struct CheckerBoard* initEmptyCheckerBoard(int length, int height) {
    struct CheckerBoard* pointer = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
    pointer->length = length;
    pointer->height = height;
    pointer->checkerBoard = (int*)malloc(sizeof(int) * pointer->length * pointer->height);
    pointer->lastModified = -1;
    pointer->zeroPosition = -1;
    return pointer;
}

// Generate checkerboard with random value.
struct CheckerBoard* initRandomCheckerBoard(int length, int height) {
    srand((unsigned)time(NULL));
    struct CheckerBoard* pointer = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
    pointer->length = length;
    pointer->height = height;
    pointer->checkerBoard = (int*)malloc(sizeof(int) * length * height);
    int cursor = 0;
    for(; cursor < pointer->length * pointer->height; cursor++) {
        pointer->checkerBoard[cursor] = cursor;
    }
    int randomNumber;
    int tempNumber;
    for(cursor--; cursor > 0; cursor--) {
        randomNumber = rand() % (length * height);
        tempNumber = pointer->checkerBoard[cursor];
        pointer->checkerBoard[cursor] = pointer->checkerBoard[randomNumber];
        pointer->checkerBoard[randomNumber] = tempNumber;
    }
    searchZeroInCheckerBoard(pointer);
    pointer->lastModified = -1;
    return pointer;
}

// Calculate the reverse pair in a checkerBoard. Wrong => -1.
int calculateReversePair(struct CheckerBoard* checkerBoard) {
    if (checkNullCheckerBoard(checkerBoard)) {
        return -65535;
    }
    int* temporary = (int*)malloc(sizeof(int) * checkerBoard->length * checkerBoard->height);
    int cursor = 0;
    int subcursor = 0;
    temporary[checkerBoard->length * checkerBoard->height - 1] = 0;
    for (; cursor < checkerBoard->length * checkerBoard->height - 1; cursor++) {
        temporary[cursor] = 0;
        for (subcursor = cursor; subcursor < checkerBoard->length * checkerBoard->height; subcursor++) {
            if (checkerBoard->checkerBoard[cursor] > checkerBoard->checkerBoard[subcursor]) {
                temporary[cursor]++;
            }
        }
    }
//    temporary[cursor + 1] = 0;
//    for (; cursor >= 0; cursor--) {
//        temporary[cursor] = 0;
//        for (subcursor = cursor + 1; subcursor < checkerBoard->length * checkerBoard->height; subcursor++) {
//            if (checkerBoard->checkerBoard[cursor] > checkerBoard->checkerBoard[subcursor]) {
//                temporary[cursor]++;
//            }
//        }
//    }
//    for (; cursor > 0; cursor--) {
//        int status = 1;
//        for (subcursor = cursor + 1; subcursor < checkerBoard->length * checkerBoard->height; subcursor++) {
//            if (checkerBoard->checkerBoard[cursor] > checkerBoard->checkerBoard[subcursor]) {
//                status = 0;
//                temporary[cursor] = temporary[subcursor] + 1;
//                break;
//            }
//        }
//        if (1 == status) {
//            temporary[cursor] = 0;
//        }
//    }
    int result = 0 - checkerBoard->zeroPosition;
//    printf("Result: %d.\n", result);
    for (cursor = 0; cursor < checkerBoard->length * checkerBoard->height; cursor++) {
        result += temporary[cursor];
//        printf("Result: %d.\n", result);
    }
    return result;
}

// Generate a paired checkerBoard from an existed one.
struct CheckerBoard* initRandomCheckerBoardWithOneExist(struct CheckerBoard* checkerBoard) {
    srand((unsigned)time(NULL));
    struct CheckerBoard* pointer = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
    pointer->length = checkerBoard->length;
    pointer->height = checkerBoard->height;
    pointer->checkerBoard = (int*)malloc(sizeof(int) * checkerBoard->length * checkerBoard->height);
    int cursor = 0;
    for(; cursor < pointer->length * pointer->height; cursor++) {
        pointer->checkerBoard[cursor] = cursor;
    }
    int randomNumber;
    int tempNumber;
    for(cursor--; cursor > 0; cursor--) {
        randomNumber = rand() % (pointer->length * pointer->height);
        tempNumber = pointer->checkerBoard[cursor];
        pointer->checkerBoard[cursor] = pointer->checkerBoard[randomNumber];
        pointer->checkerBoard[randomNumber] = tempNumber;
    }
    searchZeroInCheckerBoard(pointer);
    int left = calculateReversePair(checkerBoard) % 2;
    printf("Left: %d.\n", calculateReversePair(checkerBoard));
    while(left != (calculateReversePair(pointer) % 2)) {
        printf("Right: %d.\n", (calculateReversePair(pointer)));
        for(cursor = 0; cursor < pointer->length * pointer->height; cursor++) {
            randomNumber = rand() % (pointer->length * pointer->height);
            tempNumber = pointer->checkerBoard[cursor];
            pointer->checkerBoard[cursor] = pointer->checkerBoard[randomNumber];
            pointer->checkerBoard[randomNumber] = tempNumber;
        }
        searchZeroInCheckerBoard(pointer);
    }
    pointer->lastModified = -1;
    return pointer;
}

// Generate a pair of checkerBoard with random value.
void initTwoRandomCheckerBoard(int length, int height, struct CheckerBoard** origin, struct CheckerBoard** target) {
//    *origin = initRandomCheckerBoard(length, height);
//    printCheckerBoard(*origin);
//    *target = initRandomCheckerBoardWithOneExist(*origin);
//    printCheckerBoard(*target);

    srand((unsigned)time(NULL));
    *origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
    (*origin)->length = length;
    (*origin)->height = height;
    (*origin)->checkerBoard = (int*)malloc(sizeof(int) * length * height);
    int cursor = 0;
    for(; cursor < (*origin)->length * (*origin)->height; cursor++) {
        (*origin)->checkerBoard[cursor] = cursor;
    }
    int randomNumber;
    int tempNumber;
    for(cursor--; cursor > 0; cursor--) {
        randomNumber = rand() % (length * height);
        tempNumber = (*origin)->checkerBoard[cursor];
        (*origin)->checkerBoard[cursor] = (*origin)->checkerBoard[randomNumber];
        (*origin)->checkerBoard[randomNumber] = tempNumber;
    }
    searchZeroInCheckerBoard((*origin));
    (*origin)->lastModified = -1;


    *target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
    (*target)->length = length;
    (*target)->height = height;
    (*target)->checkerBoard = (int*)malloc(sizeof(int) * length * height);
    cursor = 0;
    for(; cursor < (*target)->length * (*target)->height; cursor++) {
        (*target)->checkerBoard[cursor] = cursor;
    }
    for(cursor--; cursor > 0; cursor--) {
        randomNumber = rand() % ((*target)->length * (*target)->height);
        tempNumber = (*target)->checkerBoard[cursor];
        (*target)->checkerBoard[cursor] = (*target)->checkerBoard[randomNumber];
        (*target)->checkerBoard[randomNumber] = tempNumber;
    }
    searchZeroInCheckerBoard((*target));
    int left = calculateReversePair(*origin) % 2;
    printf("Left: %d.\n", calculateReversePair((*origin)));
    while(left != (calculateReversePair((*target)) % 2)) {
        for(cursor = 0; cursor < (*target)->length * (*target)->height; cursor++) {
            randomNumber = rand() % ((*target)->length * (*target)->height);
            tempNumber = (*target)->checkerBoard[cursor];
            (*target)->checkerBoard[cursor] = (*target)->checkerBoard[randomNumber];
            (*target)->checkerBoard[randomNumber] = tempNumber;
        }
        searchZeroInCheckerBoard((*target));
        printf("Right: %d.\n", (calculateReversePair((*target))));
    }
    (*target)->lastModified = -1;
}

// Judge whether two checkerboard are same size, wrong input => -1, not equal => 0, equal => 1.
int judgeNotNullptrAndEqualSize(struct CheckerBoard* origin, struct CheckerBoard* target) {
    if (checkNullCheckerBoard(origin) || checkNullCheckerBoard(target)) {
        return -1;
    }
    if (origin->length != target->length || origin->height != target->height) {
        return 0;
    }
    return 1;
}

// Check whether two checkerboard are equal, wrong input => -1, not equal => 0, equal => 1.
int checkEqualCheckerBoard(struct CheckerBoard* origin, struct CheckerBoard* target) {
    if (1 != judgeNotNullptrAndEqualSize(origin, target)) {
        return -1;
    }
    int cursor = 0;
    for(; cursor < origin->length * origin->height; cursor++) {
        if (origin->checkerBoard[cursor] != target->checkerBoard[cursor]) {
            return 0;
        }
    }
    return 1;
}

// Count different number of two checkerboard. Wrong input => -1.
int countDifferenceOfCheckerBoard(struct CheckerBoard* origin, struct CheckerBoard* target) {
    int counter = 0;
    if (1 != judgeNotNullptrAndEqualSize(origin, target)) {
        return -1;
    }
    int cursor = 0;
    for(; cursor < origin->length * origin->height; cursor++) {
        if (origin->checkerBoard[cursor] != target->checkerBoard[cursor]) {
            counter++;
        }
    }
    return counter;
}

// Print the checkerboard.
void printCheckerBoard(struct CheckerBoard* checkerBoard) {
    if (checkNullCheckerBoard(checkerBoard)) {
        printf("Empty Pointer.\n");
        return;
    }
    int cursor = 0;
    for (; cursor < checkerBoard->length * checkerBoard->height; cursor++) {
        if (cursor % checkerBoard->length == 0) {
            printf("\n");
        }
        printf("%d ", checkerBoard->checkerBoard[cursor]);
    }
    printf("\n");
}

// The x and y is from range(0, length) and range(0, height);
void setValueInCheckerBoard(int x, int y, int value, struct CheckerBoard* checkerBoard) {
    if (checkNullCheckerBoard(checkerBoard)) {
        return;
    }
    checkerBoard->checkerBoard[x * checkerBoard->length + y] = value;
}

// Input value after init the checkerboard.
void inputValueInitCheckerBoard(struct CheckerBoard** checkerBoard) {
    int length;
    int height;
    if (checkNullCheckerBoard(*checkerBoard)) {
//        printf("Empty pointer.\n");
        printf("Please input length and height: ");
        scanf("%d %d", &length, &height);
        *checkerBoard = initEmptyCheckerBoard(length, height);
    }
    else {
        length = (*checkerBoard)->length;
        height = (*checkerBoard)->height;
    }
    int cursor = 0;
    for (; cursor < length * height; cursor++) {
        printf("Input Line: %d, Row: %d: ", cursor / length + 1, cursor % length + 1);
        scanf("%d", &(*checkerBoard)->checkerBoard[cursor]);
    }
    searchZeroInCheckerBoard(*checkerBoard);
    (*checkerBoard)->lastModified = -1;
}

// Get the block which can be moved. Need free after using.
int* getMoveAblePointsAndTargets(struct CheckerBoard* checkerBoard) {
    // result[0] means the length of direction.
    int* result = (int*)malloc(sizeof(int) * 5);
    result[0] = 1;
    int range = checkerBoard->height * checkerBoard->length;
    if (checkerBoard->zeroPosition - checkerBoard->length >= 0) {
        result[result[0]] = checkerBoard->zeroPosition - checkerBoard->length;
        result[0]++;
    }
    if (checkerBoard->zeroPosition + checkerBoard->length < range) {
        result[result[0]] = checkerBoard->zeroPosition + checkerBoard->length;
        result[0]++;
    }
    range = checkerBoard->zeroPosition % checkerBoard->length;
    if (range > 0) {
        result[result[0]] = checkerBoard->zeroPosition - 1;
        result[0]++;
    }
    if (range < checkerBoard->length - 1) {
        result[result[0]] = checkerBoard->zeroPosition + 1;
        result[0]++;
    }
    int cursor = 1;
    for (; cursor < result[0]; cursor++) {
        if (result[cursor] == checkerBoard->lastModified) {
            result[cursor] = result[--result[0]];
            break;
        }
    }
    return result;
}

// Move the empty block to target.
void moveInCheckerBoard(struct CheckerBoard* checkerBoard, int target) {
    if (checkNullCheckerBoard(checkerBoard)) {
        return;
    }
    checkerBoard->checkerBoard[checkerBoard->zeroPosition] = checkerBoard->checkerBoard[target];
    checkerBoard->checkerBoard[target] = 0;
    checkerBoard->lastModified = checkerBoard->zeroPosition;
    checkerBoard->zeroPosition = target;
}


// ======== Method and Test. ========
int findResultBacktracking(struct CheckerBoard* origin, struct CheckerBoard* target, struct Stack_C* stack) {
    if (1 == checkEqualCheckerBoard(origin, target)) {
        return 1;
    }
    if (stack->tail > 255) {
        return 0;
    }
    int *move = getMoveAblePointsAndTargets(origin);
    int cursor = 1;
    for (; cursor < move[0]; cursor++) {
        b++;
        struct CheckerBoard* temporary = copyCheckerBoard(origin);
        moveInCheckerBoard(temporary, move[cursor]);
        if (1 == inStack(stack, temporary)) {
            destroyCheckerBoard(temporary);
            continue;
        }
        pushStack(stack, temporary);
        if (1 == findResultBacktracking(temporary, target, stack)) {
            free(move);
            return 1;
        }
        popStack(stack);
        destroyCheckerBoard(temporary);
    }
    free(move);
    return 0;
}

void findResultByBacktracking(struct CheckerBoard* origin, struct CheckerBoard* target) {
    struct Stack_C* stack = initStack();
    pushStack(stack, origin);
    findResultBacktracking(origin, target, stack);
    displayStack(stack);
    printf("Searching steps of Backtracking algorithm: %lld.\n", b);
    int cursor = 0;
    for (; cursor < stack->tail; cursor++) {
        printCheckerBoard(stack->stack[cursor]);
		destroyCheckerBoard(stack->stack[cursor]);
        printf("\n");
    }
	destroyCheckerBoard(target);
    destroyStackOnly(stack);
    b = 0;
}

void testBacktracking_8() {

    struct CheckerBoard* origin = initEmptyCheckerBoard(3, 3);
    struct CheckerBoard* target = initEmptyCheckerBoard(3, 3);
    int cursor = 0;
    for (; cursor < 9; cursor++) {
        origin->checkerBoard[cursor] = cursor;
        target->checkerBoard[cursor] = 8 - cursor;
    }
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
    printCheckerBoard(origin);
    printCheckerBoard(target);
    findResultByBacktracking(origin, target);
//    destroyCheckerBoard(origin);
//    destroyCheckerBoard(target);
}

void testBacktracking_15() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(4, 4);
    struct CheckerBoard* target = initEmptyCheckerBoard(4, 4);
    int cursor = 0;
    for (; cursor < 16; cursor++) {
        origin->checkerBoard[cursor] = cursor;
    }
    target->checkerBoard[0] = 1;
    target->checkerBoard[1] = 2;
    target->checkerBoard[2] = 3;
    target->checkerBoard[3] = 7;
    target->checkerBoard[4] = 4;
    target->checkerBoard[5] = 5;
    target->checkerBoard[6] = 6;
    target->checkerBoard[7] = 11;
    target->checkerBoard[8] = 8;
    target->checkerBoard[9] = 9;
    target->checkerBoard[10] = 0;
    target->checkerBoard[11] = 15;
    target->checkerBoard[12] = 12;
    target->checkerBoard[13] = 13;
    target->checkerBoard[14] = 10;
    target->checkerBoard[15] = 14;
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
    printCheckerBoard(origin);
    printf("\n");
    printCheckerBoard(target);
    findResultByBacktracking(origin, target);
//    destroyCheckerBoard(origin);
//    destroyCheckerBoard(target);
}

int findResultDFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target, struct Stack_C* stack) {
    // printf("%d\n", stack->tail);
    if (checkEqualCheckerBoard(checkerBoard, target)) {
        return 1;
    }
    if (stack->tail > 255) {
        return 0;
    }
    int *move = getMoveAblePointsAndTargets(checkerBoard);
    int cursor = 1;
    for (; cursor < move[0]; cursor++) {
        struct CheckerBoard* temporary = copyCheckerBoard(checkerBoard);
        moveInCheckerBoard(temporary, move[cursor]);
        int subcursor = 0;
        int status = 1;
		if (aStarAlgorithm(checkerBoard, target) + 10 < aStarAlgorithm(temporary, target)) {
			status = 0;
			break;
		}
        for (; subcursor < stack->tail; subcursor++) {
            if (1 == checkEqualCheckerBoard(temporary, stack->stack[subcursor])) {
                status = 0;
                break;
            }
        }
        if (1 == status) {
            dfs++;
            pushStack(stack, temporary);
            if (findResultDFS(temporary, target, stack)) {
                free(move);
                return 1;
            }
            popStack(stack);
        }
        destroyCheckerBoard(temporary);
    }
    free(move);
    return 0;
}

void findResultByDFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
    struct Stack_C* stack = initStack();
    pushStack(stack, checkerBoard);
    findResultDFS(checkerBoard, target, stack);
    displayStack(stack);
    printf("DFS algorithm times: %lld.\n", dfs);
    int cursor = 0;
    for (; cursor < stack->tail; cursor++) {
        printCheckerBoard(stack->stack[cursor]);
		destroyCheckerBoard(stack->stack[cursor]);
        printf("\n");
    }
    destroyStackOnly(stack);
	destroyCheckerBoard(target);
}

int findResultDFSs(struct CheckerBoard* checkerBoard, struct CheckerBoard* target, struct Stack_C* stack) {
    if (checkEqualCheckerBoard(checkerBoard, target)) {
        return 1;
    }
    if (stack->tail > 255) {
        return 0;
    }
    int *move = getMoveAblePointsAndTargets(checkerBoard);
    int cursor = 1;
    for (; cursor < move[0]; cursor++) {
        dfs++;
        struct CheckerBoard* temporary = copyCheckerBoard(checkerBoard);
        moveInCheckerBoard(temporary, move[cursor]);
        int subcursor = 0;
        int status = 1;
        for (; subcursor < stack->tail; subcursor++) {
            if (checkEqualCheckerBoard(temporary, stack->stack[subcursor])) {
                status = 0;
                break;
            }
        }
        if (status) {
            pushStack(stack, temporary);
            if (findResultDFS(temporary, target, stack)) {
                free(move);
                return 1;
            }
            popStack(stack);
        }
        destroyCheckerBoard(temporary);
    }
    free(move);
    return 0;
}

void findResultByDFSs(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
    struct Stack_C* stack = initStack();
    pushStack(stack, checkerBoard);
    findResultDFS(checkerBoard, target, stack);
    displayStack(stack);
    printf("DFS algorithm times is: %lld.\n", dfs);
    int cursor = 0;
    for (; cursor < stack->tail; cursor++) {
        printCheckerBoard(stack->stack[cursor]);
        printf("\n");
    }
    destroyStack(stack);
}

void testDFS_8() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(3, 3);
    struct CheckerBoard* target = initEmptyCheckerBoard(3, 3);
    int cursor = 0;
    for (; cursor < 9; cursor++) {
        origin->checkerBoard[cursor] = cursor;
        target->checkerBoard[cursor] = 8 - cursor;
    }
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
    printCheckerBoard(origin);
    printCheckerBoard(target);
    findResultByDFS(origin, target);
}

void testDFS_15() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(4, 4);
    struct CheckerBoard* target = initEmptyCheckerBoard(4, 4);
    int cursor = 0;
    for (; cursor < 16; cursor++) {
        origin->checkerBoard[cursor] = cursor;
    }
    target->checkerBoard[0] = 1;
    target->checkerBoard[1] = 2;
    target->checkerBoard[2] = 3;
    target->checkerBoard[3] = 7;
    target->checkerBoard[4] = 4;
    target->checkerBoard[5] = 5;
    target->checkerBoard[6] = 6;
    target->checkerBoard[7] = 11;
    target->checkerBoard[8] = 8;
    target->checkerBoard[9] = 9;
    target->checkerBoard[10] = 0;
    target->checkerBoard[11] = 15;
    target->checkerBoard[12] = 12;
    target->checkerBoard[13] = 13;
    target->checkerBoard[14] = 10;
    target->checkerBoard[15] = 14;
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
    printCheckerBoard(origin);
    printf("\n");
    printCheckerBoard(target);
    findResultByBacktracking(origin, target);
}

int findResultBFS(struct CheckerBoard* target, struct Queue_C* queue, struct Layer* layer, struct Stack_C* stack) {
    bfs++;
    // printf("%lld size(queue)%d head(queue)%d tail(queue)%d\n", bfs, queue->size, queue->head, queue->tail);
    struct CheckerBoard* checkerBoard = popQueue(queue);
    if (NULL == checkerBoard) {
        return 0;
    }
//    pushStack(stack, checkerBoard);
    if (1 == checkEqualCheckerBoard(checkerBoard, target)) {
        // int subcursor = 0;
        // for (; subcursor < stack->tail; subcursor++) {
        // 	printCheckerBoard(stack->stack[subcursor]);
        // }
        return 1;
    }
    int *move = getMoveAblePointsAndTargets(checkerBoard);
    int cursor = 1;
    for (; cursor < move[0]; cursor++) {
        int status = 1;
        struct CheckerBoard* temporary = copyCheckerBoard(checkerBoard);
        moveInCheckerBoard(temporary, move[cursor]);
        int subcursor = 0;
        for (; subcursor < stack->tail; subcursor++) {
            if (1 == checkEqualCheckerBoard(temporary, stack->stack[subcursor])) {
                status = 0;
                destroyCheckerBoard(temporary);
                break;
            }
        }
        if (1 == status) {
            pushLayer(layer);
            pushQueue(queue, temporary); // Push temporary in fact.
            pushStack(stack, temporary);
        }
    }
    if (0 == popLayer(layer)) {
        addLayer(layer, 0);
    }
    free(move);
    return 0;
}

void findResultByBFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {

    struct Layer* layer = initLayer();
    struct Queue_C* queue = initQueue();
    struct Stack_C* stack = initStack();
    pushQueue(queue, checkerBoard);
    while (1 != findResultBFS(target, queue, layer, stack)) {}
    if (NULL != stack) {
        printf("\nStack length: %d.\n", stack->tail);
    }
    printf("BFS algorithm time: %lld.\n", bfs);
    printf("BFS depth: %d.\n", getLayer(layer) + 1);
	int cursor = 0;
	for (; cursor < stack->tail; cursor++) {
		destroyCheckerBoard(stack->stack[cursor]);
	}
    destroyStackOnly(stack);
    destroyQueue(queue);
    destroyLayer(layer);
	destroyCheckerBoard(checkerBoard);
	destroyCheckerBoard(target);
}

void testBFS_8() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(3, 3);
    struct CheckerBoard* target = initEmptyCheckerBoard(3, 3);
    int cursor = 0;
    for (; cursor < 9; cursor++) {
        origin->checkerBoard[cursor] = cursor;
        target->checkerBoard[cursor] = 8 - cursor;
    }
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
    printCheckerBoard(origin);
    printf("\n");
    printCheckerBoard(target);
    findResultByBFS(origin, target);
}

void testBFS_15() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(4, 4);
    struct CheckerBoard* target = initEmptyCheckerBoard(4, 4);
    int cursor = 0;
    for (; cursor < 16; cursor++) {
        origin->checkerBoard[cursor] = cursor;
    }
    target->checkerBoard[0] = 1;
    target->checkerBoard[1] = 2;
    target->checkerBoard[2] = 3;
    target->checkerBoard[3] = 7;
    target->checkerBoard[4] = 4;
    target->checkerBoard[5] = 5;
    target->checkerBoard[6] = 6;
    target->checkerBoard[7] = 11;
    target->checkerBoard[8] = 8;
    target->checkerBoard[9] = 9;
    target->checkerBoard[10] = 0;
    target->checkerBoard[11] = 15;
    target->checkerBoard[12] = 12;
    target->checkerBoard[13] = 13;
    target->checkerBoard[14] = 10;
    target->checkerBoard[15] = 14;
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
    printCheckerBoard(origin);
    printf("\n");
    printCheckerBoard(target);
    findResultByBFS(origin, target);
}

int aAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
    return countDifferenceOfCheckerBoard(checkerBoard, target);
}

void findResultHeuristicAAlgorithmOld(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
//    unsigned long long int local = 0;
    struct Stack_C* stack = initStack();
    struct MinHeap_C* minHeap = initMinHeap();
    // struct CheckerBoard* checkerBoard = NULL;
    // struct CheckerBoard* target = NULL;
    struct Method* method = initEmptyMethod();
    method->checkerBoard = checkerBoard;
    pushStack(method->stack, checkerBoard);
    pushStack(stack, checkerBoard);
    pushMinHeap(minHeap, method);
    while (0 == checkEqualCheckerBoard(target, checkerBoard)) {
//        displayMinHeap(minHeap);
        method = popMinHeap(minHeap);
//        printf("Score: %d.\n", method->score + method->depth);
//        printf("POP\n");
//        if (NULL == method || NULL == method->checkerBoard) {
//            printf("Empty method from minHeap\n");
//        }
        int *move = getMoveAblePointsAndTargets(method->checkerBoard);
//        printf("Get Move Able %d.\n", move[0]);
        int cursor = 1;
        struct Method* temporary = NULL;
//		for (; cursor < move[0] - 1; cursor++) {
        for (; cursor < move[0]; cursor++) {
            a++;
//            local++;
            struct CheckerBoard* temp = copyCheckerBoard(method->checkerBoard);
//            printf("Copy.\n");
            moveInCheckerBoard(temp, move[cursor]);
//            printf("Moved.\n");
            if (1 == checkEqualCheckerBoard(temp, target)) {
//                printf("Finished.\n");
//                destroyMethod(temporary);
                pushStack(method->stack, temp);
                pushStack(stack, temp);
                method->checkerBoard = temp;
                checkerBoard = temp;
                break;
            }
            int subcursor = 0;
            int status = 1;
            for (; subcursor < method->stack->tail; subcursor++) {
//                printf("Read %d...\n", method->stack->tail);
//                displayStack(method->stack);
                if (1 == checkEqualCheckerBoard(temp, (method->stack->stack[subcursor]))) {
//                    printf("Equal.\n");
                    status = 0;
                    break;
                }
            }
//            printf("Checked.\n");
            if (1 == status) {
//                printf("Start Push.\n");
                temporary = copyMethod(method);
//                displayStack(temporary->stack);
                pushStack(temporary->stack, temp);
                // Push here.
                pushStack(stack, temp);
//                displayStack(temporary->stack);
                temporary->depth++;
                temporary->checkerBoard = temp;
                temporary->score = aAlgorithm(temp, target);
                pushMinHeap(minHeap, temporary);
            }
            else {
//                printf("Else.\n");
                destroyCheckerBoard(temp);
            }
        }
    }
    printf("A algorithm times: %lld.", a);
//    printf("A algorithm times: %lld.", local);
    displayStack(method->stack);
    printf("\nLength of method: %d.\n", method->depth);
    int cursor = 0;
    for (; cursor < method->stack->tail; cursor++) {
        printCheckerBoard(method->stack->stack[cursor]);
    }
    for(cursor = 0; cursor < stack->tail; cursor++) {
        if (NULL != stack->stack[cursor]) {
            destroyCheckerBoard(stack->stack[cursor]);
            stack->stack[cursor] = NULL;
        }
    }
    destroyStackOnly(stack);
    // while (0 == isEmptyMinHeap(minHeap)) {
    // 	struct Method* me = popMinHeap(minHeap);
    // 	int subcursor = 0;
    // 	for (; subcursor < me->method->tail; subcursor++) {
    // 		destroyCheckerBoard(me->method->stack[subcursor]);
    // 	}
    // 	destroyStack(me->method);
    // 	//if (NULL != me->method) {
    // 	//	if (NULL != me->method->stack) {
    // 	//		free(me->method);
    // 	//	}
    // 	//}
    // 	destroyMethod(me);
    // }
    printf("End.\n");
    method = popMinHeap(minHeap);
    while(NULL != method) {
        destroyMethod(method);
        method = popMinHeap(minHeap);
    }
    destroyMinHeap(minHeap);
    a = 0;
}

void findResultHeuristicAAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
    struct Stack_C* stack = initStack();
    struct MinHeap_C* minHeap = initMinHeap();
    struct Method* method = initEmptyMethod();
    method->checkerBoard = checkerBoard;
    pushStack(method->stack, checkerBoard);
    pushStack(stack, checkerBoard);
    pushMinHeap(minHeap, method);
	int finish = 0;
    while (0 == checkEqualCheckerBoard(target, checkerBoard)) {
        method = popMinHeap(minHeap);
        int *move = getMoveAblePointsAndTargets(method->checkerBoard);
        int cursor = 1;
        struct Method* temporary = NULL;
        for (; cursor < move[0]; cursor++) {
            struct CheckerBoard* temp = copyCheckerBoard(method->checkerBoard);
            moveInCheckerBoard(temp, move[cursor]);
            if (1 == checkEqualCheckerBoard(temp, target)) {
                pushStack(method->stack, temp);
                method->checkerBoard = temp;
                pushStack(stack, temp);
                pushStack(stack, target);
                // checkerBoard = temp;
				finish = 1;
                break;
            }
            int subcursor = 0;
            int status = 1;
            for (; subcursor < method->stack->tail; subcursor++) {
                if (1 == checkEqualCheckerBoard(temp, (method->stack->stack[subcursor]))) {
                    status = 0;
                    break;
                }
            }
            if (1 == status) {
				a++;
                temporary = copyMethod(method);
                pushStack(temporary->stack, temp);
                temporary->depth++;
                temporary->checkerBoard = temp;
                temporary->score = aAlgorithm(temp, target);
                pushMinHeap(minHeap, temporary);
                pushStack(stack, temp);
            }
            else {
                destroyCheckerBoard(temp);
            }
        }
		free(move);
		if (0 == finish) {
			destroyMethod(method);
		}
		else {
			break;
		}
    }
    printf("A algorithm times: %lld.", a);
    displayStack(method->stack);
    printf("\nLength of method: %d.\n", method->depth);
    int cursor = 0;
    for (; cursor < method->stack->tail; cursor++) {
        printCheckerBoard(method->stack->stack[cursor]);
    }
	destroyMethod(method);
    for(cursor = 0; cursor < stack->tail; cursor++) {
        destroyCheckerBoard(stack->stack[cursor]);
    }
    destroyStackOnly(stack);
    for (cursor = 0; cursor < minHeap->tail; cursor++) {
        destroyMethod(minHeap->minHeap[cursor]);
    }
    destroyMinHeap(minHeap);
    a = 0;
}


void testA_8() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(3, 3);
    struct CheckerBoard* target = initEmptyCheckerBoard(3, 3);
    int cursor = 0;
    for (; cursor < 9; cursor++) {
        origin->checkerBoard[cursor] = cursor;
        target->checkerBoard[cursor] = 8 - cursor;
    }
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
    printCheckerBoard(origin);
    printf("\n");
    printCheckerBoard(target);
    findResultHeuristicAAlgorithm(origin, target);
}

void testA_15() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(4, 4);
    struct CheckerBoard* target = initEmptyCheckerBoard(4, 4);
    int cursor = 0;
    for (; cursor < 16; cursor++) {
        origin->checkerBoard[cursor] = cursor;
    }
    target->checkerBoard[0] = 1;
    target->checkerBoard[1] = 2;
    target->checkerBoard[2] = 3;
    target->checkerBoard[3] = 7;
    target->checkerBoard[4] = 4;
    target->checkerBoard[5] = 5;
    target->checkerBoard[6] = 6;
    target->checkerBoard[7] = 11;
    target->checkerBoard[8] = 8;
    target->checkerBoard[9] = 9;
    target->checkerBoard[10] = 0;
    target->checkerBoard[11] = 15;
    target->checkerBoard[12] = 12;
    target->checkerBoard[13] = 13;
    target->checkerBoard[14] = 10;
    target->checkerBoard[15] = 14;
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
    printCheckerBoard(origin);
    printf("\n");
    printCheckerBoard(target);
    findResultHeuristicAAlgorithm(origin, target);
}

int aStarAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
    int counter = 0;
    // Find Different Value.
    int cursor = 0;
    // Count Distance.
    if (1 != judgeNotNullptrAndEqualSize(checkerBoard, target)) {
        return 65000;
    }
    for (; cursor < target->length * target->height; cursor++) {
        if (checkerBoard->checkerBoard[cursor] != target->checkerBoard[cursor]) {
            int subCursor = 0;
            int status = 1;
            for (; subCursor < target->length * target->height; subCursor++) {
                if (checkerBoard->checkerBoard[cursor] == target->checkerBoard[subCursor]) {
                    subCursor = abs((subCursor / target->length) - (cursor / target->length))
                                + abs((subCursor % target->length) - (cursor % target->length));
                    counter += subCursor;
                    status = 0;
                    break;
                }
            }
            if (1 == status) {
                return 65000;
            }
        }
    }
    return counter;
}

void findResultHeuristicAStarAlgorithmOldVersion(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
    struct Stack_C* checker = (struct Stack_C*)malloc(sizeof(struct Stack_C));
    initStack(checker);
    struct MinHeap_C* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap_C));
    initMinHeap(minHeap);
    struct Method* method = (struct Method*)malloc(sizeof(struct Method));
    initEmptyMethod(method);
    method->checkerBoard = checkerBoard;
    pushStack(checker, checkerBoard);
    pushStack(method->stack, checkerBoard);
    pushMinHeap(minHeap, method);
    while (0 == checkEqualCheckerBoard(target, checkerBoard)) {
        method = popMinHeap(minHeap);
        int *move = (int*)malloc(sizeof(int) * 5);
        move = getMoveAblePointsAndTargets(method->checkerBoard);
        int cursor = 1;
        struct Method* temporary = NULL;
        //		for (; cursor < move[0] - 1; cursor++) {
        for (; cursor < move[0]; cursor++) {
            aStar++;
            struct CheckerBoard* temp = copyCheckerBoard(method->checkerBoard);
            moveInCheckerBoard(temp, move[cursor]);
            if (checkEqualCheckerBoard(temp, target)) {
                printf("\nSame.\n");
                destroyMethod(temporary);
                pushStack(method->stack, temp);
                method->checkerBoard = temp;
                checkerBoard = temp;
                break;
            }
            int subcursor = 0;
            int status = 1;
            for (; subcursor < checker->tail; subcursor++) {
                if (checkEqualCheckerBoard(temp, (checker->stack[subcursor]))) {
                    status = 0;
                    break;
                }
            }
            if (1 == status) {
                temporary = copyMethod(method);
                pushStack(checker, temp);
                pushStack(temporary->stack, temp);
                temporary->depth++;
                temporary->checkerBoard = temp;
                temporary->score = aStarAlgorithm(temp, target);
                pushMinHeap(minHeap, temporary);
            }
            else {
                destroyCheckerBoard(temp);
            }
        }
    }
    displayStack(method->stack);
    printf("\nLength of method: %d.\n", method->depth);
    int cursor = 0;
    for (; cursor < method->stack->tail; cursor++) {
        printCheckerBoard(method->stack->stack[cursor]);
    }
    // while (0 == isEmptyMinHeap(minHeap)) {
    // 	struct Method* me = popMinHeap(minHeap);
    // 	int subcursor = 0;
    // 	for (; subcursor < me->method->tail; subcursor++) {
    // 		destroyCheckerBoard(me->method->stack[subcursor]);
    // 	}
    // 	destroyStack(me->method);
    // 	//if (NULL != me->method) {
    // 	//	if (NULL != me->method->stack) {
    // 	//		free(me->method);
    // 	//	}
    // 	//}
    // 	destroyMethod(me);
    // }
    printf("End.\n");
    destroyMinHeap(minHeap);
    printf("A* algorithm times: %lld.", aStar);
}

void findResultHeuristicAStarAlgorithmOld(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
//    unsigned long long int local = 0;
    struct Stack_C* stack = initStack();
    struct MinHeap_C* minHeap = initMinHeap();
    // struct CheckerBoard* checkerBoard = NULL;
    // struct CheckerBoard* target = NULL;
    struct Method* method = initEmptyMethod();
    method->checkerBoard = checkerBoard;
    pushStack(method->stack, checkerBoard);
    pushMinHeap(minHeap, method);
    while (0 == checkEqualCheckerBoard(target, checkerBoard)) {
//        displayMinHeap(minHeap);
        method = popMinHeap(minHeap);
//        displayMinHeap(minHeap);
//        printf("\t\tScore out: %d.\n", method->score + method->depth);
//        int heap = 0;
//        for (; heap < minHeap->tail; heap++) {
//            printf("%d ", minHeap->minHeap[heap]->depth + minHeap->minHeap[heap]->score);
//        }
//        printf("\n");
//        printf("POP\n");
//        if (NULL == method || NULL == method->checkerBoard) {
//            printf("Empty method from minHeap\n");
//        }
        int *move = getMoveAblePointsAndTargets(method->checkerBoard);
//        printf("Get Move Able %d.\n", move[0]);
        int cursor = 1;
        struct Method* temporary = NULL;
//		for (; cursor < move[0] - 1; cursor++) {
        for (; cursor < move[0]; cursor++) {
            aStar++;
//            local++;
            struct CheckerBoard* temp = copyCheckerBoard(method->checkerBoard);
//            printf("Copy.\n");
            moveInCheckerBoard(temp, move[cursor]);
//            printf("Moved.\n");
            if (1 == checkEqualCheckerBoard(temp, target)) {
//                printf("Finished.\n");
//                destroyMethod(temporary);
                pushStack(method->stack, temp);
                pushStack(stack, temp);
                method->checkerBoard = temp;
                checkerBoard = temp;
                break;
            }
            int subcursor = 0;
            int status = 1;
            for (; subcursor < method->stack->tail; subcursor++) {
//                printf("Read %d...\n", method->stack->tail);
//                displayStack(method->stack);
                if (1 == checkEqualCheckerBoard(temp, (method->stack->stack[subcursor]))) {
//                    printf("Equal.\n");
                    status = 0;
                    break;
                }
            }
//            printf("Checked.\n");
            if (1 == status) {
//                printf("Start Push.\n");
                temporary = copyMethod(method);
//                displayStack(temporary->stack);
                pushStack(temporary->stack, temp);
                pushStack(stack, temp);
//                displayStack(temporary->stack);
                temporary->depth++;
                temporary->checkerBoard = temp;
                temporary->score = aStarAlgorithm(temp, target);
                if (65000 > temporary->score) {
//                    printf("Score in: %d.\n", temporary->score + temporary->depth);
                    pushMinHeap(minHeap, temporary);
//                    for (heap = 0; heap < minHeap->tail; heap++) {
//                        printf("%d ", minHeap->minHeap[heap]->depth + minHeap->minHeap[heap]->score);
//                    }
//                    printf("\n");
                }
                else {
                    destroyMethod(temporary);
                }
            }
            else {
//                printf("Else.\n");
                destroyCheckerBoard(temp);
            }
        }
    }
    printf("A* algorithm times: %lld.", aStar);
//    printf(" A* algorithm times: %lld.", local);
//    displayStack(method->stack);
    printf("\nLength of method: %d.\n", method->depth);
    echoResult(method->stack);
//    int cursor = 0;
//    for (; cursor < method->stack->tail; cursor++) {
//        printCheckerBoard(method->stack->stack[cursor]);
//    }

    // while (0 == isEmptyMinHeap(minHeap)) {
    // 	struct Method* me = popMinHeap(minHeap);
    // 	int subcursor = 0;
    // 	for (; subcursor < me->method->tail; subcursor++) {
    // 		destroyCheckerBoard(me->method->stack[subcursor]);
    // 	}
    // 	destroyStack(me->method);
    // 	//if (NULL != me->method) {
    // 	//	if (NULL != me->method->stack) {
    // 	//		free(me->method);
    // 	//	}
    // 	//}
    // 	destroyMethod(me);
    // }

//    printf("End.\n");
//    displayMinHeap(minHeap);
    destroyMinHeap(minHeap);
    int cursor = 0;
    for(; cursor < stack->tail; cursor++) {
        if (NULL != stack->stack[cursor]) {
            destroyCheckerBoard(stack->stack[cursor]);
            stack->stack[cursor] = NULL;
        }
    }
    destroyStackOnly(stack);
    aStar = 0;
}

void findResultHeuristicAStarAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	struct Stack_C* stack = initStack();
	struct MinHeap_C* minHeap = initMinHeap();
	struct Method* method = initEmptyMethod();
	method->checkerBoard = checkerBoard;
	pushStack(method->stack, checkerBoard);
	pushStack(stack, checkerBoard);
	pushMinHeap(minHeap, method);
	int finish = 0;
	while (0 == checkEqualCheckerBoard(target, checkerBoard)) {
		method = popMinHeap(minHeap);
		int *move = getMoveAblePointsAndTargets(method->checkerBoard);
		int cursor = 1;
		struct Method* temporary = NULL;
		for (; cursor < move[0]; cursor++) {
			struct CheckerBoard* temp = copyCheckerBoard(method->checkerBoard);
			moveInCheckerBoard(temp, move[cursor]);
			if (1 == checkEqualCheckerBoard(temp, target)) {
				pushStack(method->stack, temp);
				method->checkerBoard = temp;
				pushStack(stack, temp);
				pushStack(stack, target);
				// checkerBoard = temp;
				finish = 1;
				break;
			}
			int subcursor = 0;
			int status = 1;
			for (; subcursor < method->stack->tail; subcursor++) {
				if (1 == checkEqualCheckerBoard(temp, (method->stack->stack[subcursor]))) {
					status = 0;
					break;
				}
			}
			if (1 == status) {
				aStar++;
				temporary = copyMethod(method);
				pushStack(temporary->stack, temp);
				temporary->depth++;
				temporary->checkerBoard = temp;
				temporary->score = aStarAlgorithm(temp, target);
				pushMinHeap(minHeap, temporary);
				pushStack(stack, temp);
			}
			else {
				destroyCheckerBoard(temp);
			}
		}
		free(move);
		if (0 == finish) {
			destroyMethod(method);
		}
		else {
			break;
		}
	}
	printf("A* algorithm times: %lld.", aStar);
	displayStack(method->stack);
	printf("\nLength of method: %d.\n", method->depth);
	int cursor = 0;
	for (; cursor < method->stack->tail; cursor++) {
		printCheckerBoard(method->stack->stack[cursor]);
	}
	destroyMethod(method);
	for (cursor = 0; cursor < stack->tail; cursor++) {
		destroyCheckerBoard(stack->stack[cursor]);
	}
	destroyStackOnly(stack);
	for (cursor = 0; cursor < minHeap->tail; cursor++) {
		destroyMethod(minHeap->minHeap[cursor]);
	}
	destroyMinHeap(minHeap);
	a = 0;
}


void testAStar_8() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(3, 3);
    struct CheckerBoard* target = initEmptyCheckerBoard(3, 3);
    int cursor = 0;
    for (; cursor < 9; cursor++) {
        origin->checkerBoard[cursor] = cursor;
        target->checkerBoard[cursor] = 8 - cursor;
    }
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
    printCheckerBoard(origin);
    printf("\n");
    printCheckerBoard(target);
    findResultHeuristicAStarAlgorithm(origin, target);
}

void testAStar_15() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(4, 4);
    struct CheckerBoard* target = initEmptyCheckerBoard(4, 4);
    int cursor = 0;
    for (; cursor < 16; cursor++) {
        origin->checkerBoard[cursor] = cursor;
    }
    target->checkerBoard[0] = 1;
    target->checkerBoard[1] = 2;
    target->checkerBoard[2] = 3;
    target->checkerBoard[3] = 7;
    target->checkerBoard[4] = 4;
    target->checkerBoard[5] = 5;
    target->checkerBoard[6] = 6;
    target->checkerBoard[7] = 11;
    target->checkerBoard[8] = 8;
    target->checkerBoard[9] = 9;
    target->checkerBoard[10] = 0;
    target->checkerBoard[11] = 15;
    target->checkerBoard[12] = 12;
    target->checkerBoard[13] = 13;
    target->checkerBoard[14] = 10;
    target->checkerBoard[15] = 14;
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
//    printCheckerBoard(origin);
//    printf("\n");
//    printCheckerBoard(target);
    findResultHeuristicAStarAlgorithm(origin, target);
}

void findResultByHeuristic(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {

}

void findResultByRandom(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {

}

void testing() {
    testBacktracking_8();
	system("pause");
    testDFS_8();
	system("pause");
    testBFS_15();
	system("pause");
    testA_8();
	system("pause");
    testA_15();
	system("pause");
    testAStar_8();
	system("pause");
    testAStar_15();
	system("pause");
    // exit(0);
}

void testBackTracking() {
    testBacktracking_8();
    exit(0);
}

void testDFS() {
    testDFS_8();
    exit(0);
}

void testBFS() {
    testBFS_8();
    exit(0);
}

void testA() {
    testA_8();
    testA_15();
    exit(0);
}

void testAStar() {
    testAStar_8();
    testAStar_15();
    exit(0);
}

void testInputAStar() {
    struct CheckerBoard* origin = NULL; // (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
    // struct CheckerBoard* target = NULL; // (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
    printf("Please input checkerboard 1:\n");
    inputValueInitCheckerBoard(&origin);
    struct CheckerBoard* target = initEmptyCheckerBoard(origin->length, origin->height);
    printf("Please input checkerboard 2:\n");
    inputValueInitCheckerBoard(&target);
    int left = calculateReversePair(origin) % 2;
    int right = calculateReversePair(target) % 2;
    while (left != right) {
        inputValueInitCheckerBoard(&target);
        right = calculateReversePair(target) % 2;
    }
    findResultHeuristicAStarAlgorithm(origin, target);
}

void testRandomAStar() {
    struct CheckerBoard *origin = NULL;
    struct CheckerBoard *target = NULL;
    initTwoRandomCheckerBoard(3, 3, &origin, &target);
    printCheckerBoard(origin);
    printCheckerBoard(target);
    findResultHeuristicAStarAlgorithm(origin, target);
    exit(0);
}

void echoResult(struct Stack_C* stack) {
    if (isEmptyStack(stack)) {
        return;
    }
    int cursor = 0;
    for (; cursor < stack->tail; cursor++) {
        printCheckerBoard(stack->stack[cursor]);
    }
}
