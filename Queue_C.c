#pragma warning(disable:4996)
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "Queue_C.h"

int isEmptyQueue(struct Queue_C* queue) {
	if (NULL == queue) {
		return 1;
	}
	if (NULL == queue->queue) {
		return 1;
	}
	if (0 == queue->tail && 0 == queue->head) {
		return 1;
	}
	return 0;
}

int initQueue(struct Queue_C* queue) {
	queue->head = 0;
	queue->tail = 0;
	queue->size = 16;
	queue->queue = (struct Queue_C**)malloc(sizeof(struct Queue_C*) * 16);
	return 0;
}

void extendQueue(struct Queue_C* queue) {
	int cursor = 0;
	int newSize = queue->size;
	newSize = newSize << 1;
	int *newArray = (struct Queue_C**)malloc(sizeof(struct Queue_C*) * newSize);
	if (queue->head >= queue->tail) {
		for (; cursor + queue->head < queue->size; cursor++) {
			newArray[cursor] = queue->queue[queue->head + cursor];
		}
		int length = cursor;
		for (; cursor - length < queue->tail; cursor++) {
			newArray[cursor] = queue->queue[cursor - length];
		}
	}
	else {
		for (; cursor < queue->tail; cursor++) {
			newArray[cursor] = queue->queue[cursor];
		}
	}
	free(queue->queue);
	queue->head = 0;
	queue->tail = cursor;
	queue->queue = newArray;
	queue->size = newSize;
}

int pushQueue(struct Queue_C* queue, struct CheckerBoard* value)
{
	if (NULL == queue) {
		return -65535;
	}
	if (NULL == queue->queue) {
		return -65535;
	}
	if (queue->head == queue->tail) {
		if (0 == queue->head) {
			// Only empty means 0 == head && 0 == tail.
			// Extend when 0 == head and size == tail.
			queue->queue[queue->tail++] = value;
			return 1;
		}
		else {
			extendQueue(queue);
		}
	}
	else if (queue->tail == queue->size) {
		if (0 == queue->head) {
			extendQueue(queue);
		}
		else {
			queue->tail = 0;
		}
	}
	queue->queue[queue->tail++] = value;
	return 1;
}

struct CheckerBoard* popQueue(struct Queue_C* queue) {
	if (NULL == queue) {
		return NULL;
	}
	if (NULL == queue->queue) {
		return NULL;
	}
	int result;
	if (queue->head < queue->tail) {
		result = queue->queue[queue->head++];
		if (queue->head == queue->tail) {
			queue->head = queue->tail = 0;
		}
	}
	else {
		result = queue->queue[queue->head++];
		if (queue->head == queue->size) {
			if (0 == queue->tail) {
				extendQueue(queue);
			}
			else {
				queue->head = 0;
			}
		}
	}
	return result;
}

void destoryQueue(struct Queue_C* queue) {
	if (NULL == queue) {
		return;
	}
	if (NULL == queue->queue) {
		return;
	}
	else {
		int cursor = 0;
		struct CheckerBoard* temp = NULL;
		while (1) {
			if (isEmptyQueue(queue)) {
				break;
			}
			temp = popQueue(queue);
			if (NULL == temp) {
				break;
			}
			else {
				destroyCheckerBoard(temp);
				// free(temp);
			}
		}
		free(queue->queue);
	}
}

void displayQueue(struct Queue_C* queue) {
	if (isEmptyQueue(queue) == 0) {
		int cursor;
		printf("\nHead: %d, tail: %d\n", queue->head, queue->tail);
		// for (cursor = 0; cursor < queue->size; cursor++) {
		// 	printf("%d ", queue->queue[cursor]);
		// }
		// printf("\n");
		if (queue->head < queue->tail) {
			printf("Length: %d\n", queue->tail - queue->head);
			for (cursor = queue->head; cursor < queue->tail; cursor++) {
				printf("%#X ", queue->queue[cursor]);
			}
		}
		else {
			printf("Length: %d\n", queue->size - queue->head + queue->tail);
			for (cursor = queue->head; cursor < queue->size; cursor++) {
				printf("%#X ", queue->queue[cursor]);
			}
			for (cursor = 0; cursor < queue->tail; cursor++) {
				printf("%#X ", queue->queue[cursor]);
			}
		}
		printf("\n");
	}
	else {
		printf("\nEmpty queue.\n");
	}
}

void testQueue() {
	struct Queue_C* queue = (struct Queue_C*)malloc(sizeof(struct Queue_C));
	initQueue(queue);
	int cursor = 0;
	for (; cursor < 33; cursor++) {
		struct CheckerBoard* checkerBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
		initRandomCheckerBoard(3, 3, checkerBoard);
		pushQueue(queue, checkerBoard);
	}
	displayQueue(queue);
	for (cursor = 0; cursor < 33; cursor++) {
		struct CheckerBoard* checkerBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
		checkerBoard = popQueue(queue);
		printCheckerBoard(checkerBoard);
		destroyCheckerBoard(checkerBoard);
	}
	displayQueue(queue);
	destoryQueue(queue);
	free(queue);
	queue = (struct Queue_C*)malloc(sizeof(struct Queue_C));
	initQueue(queue);
	for (cursor = 0; cursor < 15; cursor++) {
		struct CheckerBoard* checkerBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
		initRandomCheckerBoard(3, 3, checkerBoard);
		pushQueue(queue, checkerBoard);
	}
	for (cursor = 0; cursor < 10; cursor++) {
		struct CheckerBoard* checkerBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
		checkerBoard = popQueue(queue);
		destroyCheckerBoard(checkerBoard);
	}
	displayQueue(queue);
	for (cursor = 0; cursor < 60; cursor++) {
		struct CheckerBoard* checkerBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
		initRandomCheckerBoard(3, 3, checkerBoard);
		pushQueue(queue, checkerBoard);
	}
	displayQueue(queue);
	int max = 65;
	max = 60;
	for (cursor = 0; cursor < max; cursor++) {
		struct CheckerBoard* checkerBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
		checkerBoard = popQueue(queue);
		destroyCheckerBoard(checkerBoard);
	}
	displayQueue(queue);
	destoryQueue(queue);
	free(queue);
}
