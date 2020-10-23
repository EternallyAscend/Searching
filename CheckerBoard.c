#pragma warning(disable:4996)
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include"Layer.h"
#include"Random.h"
#include"Queue_C.h"
#include"Stack_C.h"
#include"MinHeap_C.h"
#include"CheckerBoard.h"

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

//struct Method {
//	int depth; // Store current searching depth.
//	int score; // Using it in A or A* Algorithm.
//	int nodeCounter; // Record all reached nodes.
//	struct CheckerBoard *checkerBoard; // Current.
//	struct Stack *method; // History with current.
//};

void initEmptyMethod(struct Method* method) {
	method->depth = 0;
	method->score = 0;
	method->nodeCounter = 0;
	method->checkerBoard = NULL;
	method->method = (struct Stack_C*)malloc(sizeof(struct Stack_C));
	initStack(method->method);
}

int isNullMethod(struct Method* method) {
	if (NULL == method) {
		return 1;
	}
	else if (checkNullCheckerBoard(method->checkerBoard)) {
		return 1;
	}
	else if (NULL == method->method) {
		return 1;
	}
	return 0;
}

struct Method* copyMethod(struct Method* method) {
	struct Method* copy = (struct Method*)malloc(sizeof(struct Method));
	copy->depth = method->depth;
	copy->score = method->score;
	copy->nodeCounter = method->nodeCounter;
	copy->checkerBoard = method->checkerBoard;
	copy->method = copyStack(method->method);
	return copy;
}

int destroyMethod(struct Method* method) {
	if (NULL == method) {
		return 0;
	}
	if (NULL != method->method) {
		free(method->method);
	}
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

// Copy a new checkerboard with same situation.
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

int checkNullCheckerBoard(struct CheckerBoard* checkerBoard) {
	// 1 means null.
	// 0 means not null.
	if (NULL == checkerBoard) {
		return 1;
	}
	else {
		if (NULL == checkerBoard->checkerBoard) {
			return 1;
		}
	}
	return 0;
}

// Check whether two checkerboard are equal, wrong input => -1, not equal => 0, equal => 1.
int checkEqualCheckerBoard(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	// -1 means wrong input.
	// 0 means they are not equal.
	// 1 means they are equal.
	if (checkNullCheckerBoard(checkerBoard) || checkNullCheckerBoard(target)) {
		return -1;
	}
	if (checkerBoard->length != checkerBoard->length || checkerBoard->height != checkerBoard->height) {
		return -1;
	}
	int item = 0;
	for (; item < checkerBoard->length * checkerBoard->height; item++) {
		if (checkerBoard->checkerBoard[item] != target->checkerBoard[item]) {
			return 0;
		}
	}
	return 1;
}

// Judge whether two checkerboard are same size, wrong input => -1, not equal => 0, equal => 1.
int judgeNotNullptrAndEqualSize(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	// -1 means wrong input.
	// 0 means they are not equal.
	// 1 means they are equal.
	if (checkNullCheckerBoard(checkerBoard) || checkNullCheckerBoard(target)) {
		return -1;
	}
	if (checkerBoard->length != checkerBoard->length || checkerBoard->height != checkerBoard->height) {
		return 0;
	}
	return 1;
}

// Count different number of two checkerboard. Wrong input => -1.
int countDifferenceOfCheckerBoard(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	if (!judgeNotNullptrAndEqualSize(checkerBoard, target)) {
		return -1;
	}
	int item = 0;
	int counter = 0;
	for (; item < checkerBoard->length * checkerBoard->height; item++) {
		if (checkerBoard->checkerBoard[item] != target->checkerBoard[item]) {
			counter++;
		}
	}
	return counter;
}

// Find position of empty block. Wrong input => -1;
void searchZeroInCheckerBoard(struct CheckerBoard* checkerBoard) {
	if (checkNullCheckerBoard(checkerBoard)) {
		return -1;
	}
	int item = 0;
	for (; item < checkerBoard->length * checkerBoard->height; item++) {
		if (checkerBoard->checkerBoard[item] == 0) {
			checkerBoard->zeroPosition = item;
			return;
		}
	}
}

// Init the checkerboard without any useful value.
void initCheckerBoard(int length, int height, struct CheckerBoard* checkerBoard) {
	checkerBoard->length = length;
	checkerBoard->height = height;
	checkerBoard->checkerBoard = (int*)malloc(sizeof(int) * length * height);
	checkerBoard->lastModified = -1;
}

// Generate checkerboard with random value.
void initRandomCheckerBoard(int length, int height, struct CheckerBoard* checkerBoard) {
	checkerBoard->length = length;
	checkerBoard->height = height;
	checkerBoard->checkerBoard = (int*)malloc(sizeof(int) * length * height);
	int item = 0;
	for (; item < length * height; item++) {
		checkerBoard->checkerBoard[item] = item;
	}
	srand((unsigned)time(NULL));
	for (item = 0; item < length * height; item++) {
		int randomNumber = rand() % (length * height);
		int current = checkerBoard->checkerBoard[item];
		checkerBoard->checkerBoard[item] = checkerBoard->checkerBoard[randomNumber];
		checkerBoard->checkerBoard[randomNumber] = current;
	}
	searchZeroInCheckerBoard(checkerBoard);
	checkerBoard->lastModified = -1;
}

// Print the checkerboard.
void printCheckerBoard(struct CheckerBoard* checkerBoard) {
	if (checkNullCheckerBoard(checkerBoard)) {
		return;
	}
	int i = 0;
	printf("The checkerBoard is:");
	for (; i < checkerBoard->length * checkerBoard->height; i++) {
		if (i % checkerBoard->length == 0) {
			printf("\n");
		}
		printf("%d ", checkerBoard->checkerBoard[i]);
	}
}

void setValueInCheckerBoard(int x, int y, int value, struct CheckerBoard* checkerBoard) {
	if (checkNullCheckerBoard(checkerBoard)) {
		return;
	}
	// The x and y is from range(0, length) and range(0, height);
	checkerBoard->checkerBoard[y * checkerBoard->length + x] = value;
}

// Input value after init the checkerboard.
void inputValueInitCheckerBoard(struct CheckerBoard* checkerBoard) {
	printf("Please input target checkerBoard:");
	int item = 0;
	int current;
	for (; item < checkerBoard->length * checkerBoard->height; item++) {
		scanf("%d", &current);
		checkerBoard->checkerBoard[item] = current;
	}
	searchZeroInCheckerBoard(checkerBoard);
}

// Get the block which can be moved.
int* getMoveAblePointsAndTargets(struct CheckerBoard* checkerBoard) {
	// result[0] means the length of direction.
	int* result = (int*)malloc(sizeof(int) * 5);
	result[0] = 1;
	int range = checkerBoard->height * checkerBoard->length;
	if (checkerBoard->zeroPosition - checkerBoard->length > 0) {
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

void destroyCheckerBoard(struct CheckerBoard* checkerBoard) {
	if (checkNullCheckerBoard(checkerBoard)) {
		return;
	}
	if (NULL == checkerBoard->checkerBoard) {
		free(checkerBoard);
		return;
	}
	free(checkerBoard->checkerBoard);
	free(checkerBoard);
}

int findResultBacktracking(struct CheckerBoard* checkerBoard, struct CheckerBoard* target, struct Stack_C* stack) {
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
		pushStack(stack, temporary);
		if (findResultDFS(temporary, target, stack)) {
			free(move);
			return 1;
		}
		popStack(stack);
		destroyCheckerBoard(temporary);
	}
	free(move);
	return 0;
}

void findResultByBacktracking(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	struct Stack_C* stack = (struct Stack_C*)malloc(sizeof(struct Stack_C));
	initStack(stack);
	pushStack(stack, checkerBoard);
	findResultDFS(checkerBoard, target, stack);
	displayStack(stack);
	printf("Searching steps of Backtracking algorithm: %lld.\n", dfs);
	int cursor = 0;
	for (; cursor < stack->tail; cursor++) {
		printCheckerBoard(stack->stack[cursor]);
		printf("\n");
	}
	destroyStack(stack);
	free(stack);
}

void testBacktracking_8() {
	struct CheckerBoard* origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	struct CheckerBoard* target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	initCheckerBoard(3, 3, origin);
	initCheckerBoard(3, 3, target);
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
	findResultByBacktracking(origin, target);
	destroyCheckerBoard(origin);
	destroyCheckerBoard(target);
}

void testBacktracking_15() {
	struct CheckerBoard* origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	struct CheckerBoard* target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	initCheckerBoard(4, 4, origin);
	initCheckerBoard(4, 4, target);
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
	destroyCheckerBoard(origin);
	destroyCheckerBoard(target);
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

void findResultByDFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	struct Stack_C* stack = (struct Stack_C*)malloc(sizeof(struct Stack_C));
	initStack(stack);
	pushStack(stack, checkerBoard);
	findResultDFS(checkerBoard, target, stack);
	displayStack(stack);
	printf("%d\n", dfs);
	int cursor = 0;
	for (; cursor < stack->tail; cursor++) {
		printCheckerBoard(stack->stack[cursor]);
		printf("\n");
	}
	destroyStack(stack);
	free(stack);
}

struct Stack_C* findResultBFSs(struct CheckerBoard* target, struct Queue_C* queue, struct Layer* layer, struct Stack_C* stack) {
	bfs++;
	printf("%lld size(queue)%d head(queue)%d tail(queue)%d\n", bfs, queue->size, queue->head, queue->tail);
	struct CheckerBoard* checkerBoard = popQueue(queue);
	if (NULL == checkerBoard) {
		return NULL;
	}
	struct Stack_C* currentStack = copyStack(stack);
	// destroyStack(stack);
	free(stack);
	pushStack(currentStack, checkerBoard);
	if (checkEqualCheckerBoard(checkerBoard, target)) {
		displayStack(currentStack);
		int subcursor = 0;
		for (; subcursor < currentStack->tail; subcursor++) {
			printCheckerBoard(currentStack->stack[subcursor]);
		}
		return currentStack;
	}
//	int length = queue->tail;
	int *move = getMoveAblePointsAndTargets(checkerBoard);
	int cursor = 1;
	for (; cursor < move[0]; cursor++) {
		int status = 1;
		struct CheckerBoard* temporary = copyCheckerBoard(checkerBoard);
		moveInCheckerBoard(temporary, move[cursor]);
		pushLayer(layer);
		int subcursor = 0;
		for (; subcursor < currentStack->tail; subcursor++) {
			if (checkEqualCheckerBoard(temporary, currentStack->stack[subcursor])) {
				status = 0;
				break;
			}
		}
		if (1 == status) {
			pushQueue(queue, temporary); // Push temporary in fact.
		}
	}
//  if (length == getLayerPosition(layer, getLayer(layer))) {
//  	addLayer(layer, queue->tail);
//  }

	if (0 == popLayer(layer)) {
		addLayer(layer, 0);
	}

	// Replace checkerBoard with popQueue(queue) in fact.
	free(move);
	// destroyCheckerBoard(checkerBoard);

	return (findResultBFSs(target, queue, layer, currentStack));
//	return (findResultBFS(target, queue, layer, stack));
}

int findResultBFSss(struct CheckerBoard* target, struct Queue_C* queue, struct Layer* layer, struct Stack_C* stack) {
	bfs++;
	// printf("%lld size(queue)%d head(queue)%d tail(queue)%d\n", bfs, queue->size, queue->head, queue->tail);
	struct CheckerBoard* checkerBoard = popQueue(queue);
	if (NULL == checkerBoard) {
		return 0;
	}
	pushStack(stack, checkerBoard);
	if (checkEqualCheckerBoard(checkerBoard, target)) {
		int subcursor = 0;
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
			if (checkEqualCheckerBoard(temporary, stack->stack[subcursor])) {
				status = 0;
				destroyCheckerBoard(temporary);
				break;
			}
		}
		if (1 == status) {
			pushLayer(layer);
			pushQueue(queue, temporary); // Push temporary in fact.
		}
	}
	if (0 == popLayer(layer)) {
		addLayer(layer, 0);
	}
	free(move);
	return 0;
}

int findResultBFS(struct CheckerBoard* target, struct Queue_C* queue, struct Layer* layer, struct Stack_C* stack) {
	bfs++;
	printf("%lld size(queue)%d head(queue)%d tail(queue)%d\n", bfs, queue->size, queue->head, queue->tail);

	struct CheckerBoard* checkerBoard = popQueue(queue);
	if (NULL == checkerBoard) {
		return 0;
	}
	if (checkEqualCheckerBoard(checkerBoard, target)) {
		printCheckerBoard(checkerBoard);
		return 1;
	}
	//	int length = queue->tail;
	int *move = getMoveAblePointsAndTargets(checkerBoard);
	int cursor = 1;
	for (; cursor < move[0]; cursor++) {
		struct CheckerBoard* temporary = copyCheckerBoard(checkerBoard);
		moveInCheckerBoard(temporary, move[cursor]);
		pushQueue(queue, temporary); // Push temporary in fact.
		pushLayer(layer);
	}
	//  if (length == getLayerPosition(layer, getLayer(layer))) {
	//  	addLayer(layer, queue->tail);
	//  }

	if (0 == popLayer(layer)) {
		addLayer(layer, 0);
	}

	// Replace checkerBoard with popQueue(queue) in fact.
	free(move);
}

void findResultByBFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	struct Layer* layer = (struct Layer*)malloc(sizeof(struct Layer));
	initLayer(layer);
	struct Queue_C* queue = (struct Queue_C*)malloc(sizeof(struct Queue_C));
	initQueue(queue);
	struct Stack_C* stack = (struct Stack_C*)malloc(sizeof(struct Stack_C));
	initStack(stack);
	pushQueue(queue, checkerBoard);
//	stack = findResultBFSss(target, queue, layer, stack);
	while (1 != findResultBFSss(target, queue, layer, stack)) {}
	if (NULL != stack) {
		printf("\nStack length: %d.\n", stack->tail);
	}
	// while (1 != findResultBFS(target, queue, layer, stack)) {}
	printf("BFS algoritm time: %lld.\n", bfs);
	printf("BFS depth: %d.\n", getLayer(layer) + 1);
	destoryQueue(queue);
	free(queue);
}

void testBFS_8() {
	struct CheckerBoard* origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	struct CheckerBoard* target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	initCheckerBoard(3, 3, origin);
	initCheckerBoard(3, 3, target);
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
	destroyCheckerBoard(origin);
	destroyCheckerBoard(target);
}

void testBFS_15() {

	struct CheckerBoard* origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	struct CheckerBoard* target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	initCheckerBoard(4, 4, origin);
	initCheckerBoard(4, 4, target);
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
	destroyCheckerBoard(origin);
	destroyCheckerBoard(target);
}

int aAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	return countDifferenceOfCheckerBoard(checkerBoard, target);
}

int aStarAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	int counter = 0;
	// Find Different Value.
	int cursor = 0;
	// Count Distance.
	if (judgeNotNullptrAndEqualSize(checkerBoard, target)) {

	}
	for (; cursor < target->length * target->height; cursor++) {
		if (checkerBoard->checkerBoard[cursor] != target->checkerBoard[cursor]) {
			int subCursor = 0;
			for (; subCursor < target->length * target->height; subCursor++) {
				if (checkerBoard->checkerBoard[cursor] == target->checkerBoard[subCursor]) {
					break;
				}
			}
			subCursor = abs((subCursor / target->length) - (cursor / target->length))
						+ abs((subCursor % target->length) - (cursor % target->length));
			counter += subCursor;
		}
	}
	return counter;
}

void findResultHeuristicAAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	struct MinHeap_C* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap_C));
	initMinHeap(minHeap);
	// struct CheckerBoard* checkerBoard = NULL;
	// struct CheckerBoard* target = NULL;
	struct Method* method = (struct Method*)malloc(sizeof(struct Method));
	initEmptyMethod(method);
	method->checkerBoard = checkerBoard;
	pushStack(method->method, checkerBoard);
	pushMinHeap(minHeap, method);
	while (0 == checkEqualCheckerBoard(target, checkerBoard)) {
		method = popMinHeap(minHeap);
		int *move = (int*)malloc(sizeof(int) * 5);
		move = getMoveAblePointsAndTargets(method->checkerBoard);
		int cursor = 1;
		struct Method* temporary = NULL;
//		for (; cursor < move[0] - 1; cursor++) {
		for (; cursor < move[0]; cursor++) {
			a++;
			struct CheckerBoard* temp = copyCheckerBoard(method->checkerBoard);
			moveInCheckerBoard(temp, move[cursor]);
			if (checkEqualCheckerBoard(temp, target)) {
				printf("");
				destroyMethod(temporary);
				pushStack(method->method, temp);
				method->checkerBoard = temp;
				checkerBoard = temp;
				break;
			}
			int subcursor = 0;
			int status = 1;
			for (; subcursor < method->method->tail; subcursor++) {
				if (checkEqualCheckerBoard(temp, (method->method->stack[subcursor]))) {
					status = 0;
					break;
				}
			}
			if (1 == status) {
				temporary = copyMethod(method);
				pushStack(temporary->method, temp);
				temporary->depth++;
				temporary->checkerBoard = temp;
				temporary->score = aAlgorithm(temp, target);
				pushMinHeap(minHeap, temporary);
			}
			else {
				destroyCheckerBoard(temp);
			}
		}
	}
	displayStack(method->method);
	printf("\nLength of method: %d.\n", method->depth);
	int cursor = 0;
	for (; cursor < method->method->tail; cursor++) {
		printCheckerBoard(method->method->stack[cursor]);
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
	destoryMinHeap(minHeap);
	printf("A algorithm times: %d.", a);
}

void findResultByHeuristicAAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	struct Stack_C* checker = (struct Stack_C*)malloc(sizeof(struct Stack_C));
	initStack(checker);
	struct MinHeap_C* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap_C));
	initMinHeap(minHeap);
	struct Method* method = (struct Method*)malloc(sizeof(struct Method));
	initEmptyMethod(method);
	method->checkerBoard = checkerBoard;
	pushStack(checker, checkerBoard);
	pushStack(method->method, checkerBoard);
	pushMinHeap(minHeap, method);
	while (0 == checkEqualCheckerBoard(target, checkerBoard)) {
		method = popMinHeap(minHeap);
		int *move = (int*)malloc(sizeof(int) * 5);
		move = getMoveAblePointsAndTargets(method->checkerBoard);
		int cursor = 1;
		struct Method* temporary = NULL;
		//		for (; cursor < move[0] - 1; cursor++) {
		for (; cursor < move[0]; cursor++) {
			a++;
			struct CheckerBoard* temp = copyCheckerBoard(method->checkerBoard);
			moveInCheckerBoard(temp, move[cursor]);
			if (checkEqualCheckerBoard(temp, target)) {
				printf("\nSame.\n");
				destroyMethod(temporary);
				pushStack(method->method, temp);
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
				pushStack(temporary->method, temp);
				temporary->depth++;
				temporary->checkerBoard = temp;
				temporary->score = aAlgorithm(temp, target);
				pushMinHeap(minHeap, temporary);
			}
			else {
				destroyCheckerBoard(temp);
			}
		}
	}
	displayStack(method->method);
	printf("\nLength of method: %d.\n", method->depth);
	int cursor = 0;
	for (; cursor < method->method->tail; cursor++) {
		printCheckerBoard(method->method->stack[cursor]);
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
	destoryMinHeap(minHeap);
	printf("A algorithm times: %d.", a);
}

void testA_8() {
	struct CheckerBoard* origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	struct CheckerBoard* target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	initCheckerBoard(3, 3, origin);
	initCheckerBoard(3, 3, target);
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
	findResultByHeuristicAAlgorithm(origin, target);
	destroyCheckerBoard(origin);
	destroyCheckerBoard(target);
}

void testA_15() {

	struct CheckerBoard* origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	struct CheckerBoard* target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	initCheckerBoard(4, 4, origin);
	initCheckerBoard(4, 4, target);
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
	findResultByHeuristicAAlgorithm(origin, target);
	destroyCheckerBoard(origin);
	destroyCheckerBoard(target);
}

void findResultHeuristicAStarAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	struct Stack_C* checker = (struct Stack_C*)malloc(sizeof(struct Stack_C));
	initStack(checker);
	struct MinHeap_C* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap_C));
	initMinHeap(minHeap);
	struct Method* method = (struct Method*)malloc(sizeof(struct Method));
	initEmptyMethod(method);
	method->checkerBoard = checkerBoard;
	pushStack(checker, checkerBoard);
	pushStack(method->method, checkerBoard);
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
				pushStack(method->method, temp);
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
				pushStack(temporary->method, temp);
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
	displayStack(method->method);
	printf("\nLength of method: %d.\n", method->depth);
	int cursor = 0;
	for (; cursor < method->method->tail; cursor++) {
		printCheckerBoard(method->method->stack[cursor]);
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
	destoryMinHeap(minHeap);
	printf("A* algorithm times: %d.", aStar);

}


void testAStar_8() {
	struct CheckerBoard* origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	struct CheckerBoard* target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	initCheckerBoard(3, 3, origin);
	initCheckerBoard(3, 3, target);
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
	destroyCheckerBoard(origin);
	destroyCheckerBoard(target);
}

void testAStar_15() {

	struct CheckerBoard* origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	struct CheckerBoard* target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	initCheckerBoard(4, 4, origin);
	initCheckerBoard(4, 4, target);
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
	findResultHeuristicAStarAlgorithm(origin, target);
	destroyCheckerBoard(origin);
	destroyCheckerBoard(target);
}


void findResultByHeuristic(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	struct MinHeap_C* minHeap = (struct MinHeap_C*)malloc(sizeof(struct MinHeap_C));
	initMinHeap(minHeap);

	destoryMinHeap(minHeap);
	free(minHeap);
}

void findResultByRandom(struct CheckerBoard* checkerBoard, struct CheckerBoard* target) {
	struct MinHeap_C *minHeap = (struct MinHeap_C*)malloc(sizeof(struct MinHeap_C));
	initMinHeap(minHeap);

	destoryMinHeap(minHeap);
	free(minHeap);
}


//int main(void) {
//	testMinHeap();
//	testMaxHeap();
	// testQueue();

	/*
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	initStack(stack);
	int* randomIntArray = getRandomIntArrayByRange(33, 100);
	int cursor = 0;
	for (; cursor < 33; cursor++) {
		pushStack(stack, randomIntArray[cursor]);
		displayStack(stack);
		if (cursor == 0) {
			printf("Length: %d\n", stack->tail);
			printf("Pop: %d\n", popStack(stack));
			printf("Length: %d\n", stack->tail);
		}
	}
	printf("Pop: %d\n", popStack(stack));
	printf("Length: %d\n", stack->tail);
	free(randomIntArray);
	destroyStack(stack);
	free(stack);
	*/

	//printf("Please input the length and height of the checkerBoard:");
	//int length;
	//int height;
	//scanf("%d %d", &length, &height);
	//struct CheckerBoard* checkBoard;
	//checkBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	//initRandomCheckerBoard(length, height, checkBoard);
	//struct CheckerBoard* target;
	//target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	//initCheckerBoard(length, height, target);
	//inputValueInitCheckerBoard(target);
	//printCheckerBoard(checkBoard);
	//free(checkBoard);
	//free(target);
//	return 0;
//}
