#pragma warning(disable:4996)
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "Queue.h"

int isEmptyQueue(struct Queue* queue) {
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

int initQueue(struct Queue* queue) {
	queue->head = 0;
	queue->tail = 0;
	queue->size = 16;
	queue->queue = (int*)malloc(sizeof(int) * 16);
	return 0;
}

void extendQueue(struct Queue* queue) {
	int cursor = 0;
	int newSize = queue->size;
	newSize = newSize << 1;
	int *newArray = (int*)malloc(sizeof(int) * newSize);
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

int pushQueue(struct Queue* queue, int value)
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

int popQueue(struct Queue* queue) {
	if (NULL == queue) {
		return -65535;
	}
	if (NULL == queue->queue) {
		return -65535;
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

void destoryQueue(struct Queue* queue) {
	if (NULL == queue) {
		return;
	}
	if (NULL == queue->queue) {
		return;
	}
	else {
		free(queue->queue);
	}
}

void displayQueue(struct Queue * queue) {
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
				printf("%d ", queue->queue[cursor]);
			}
		}
		else {
			printf("Length: %d\n", queue->size - queue->head + queue->tail);
			for (cursor = queue->head; cursor < queue->size; cursor++) {
				printf("%d ", queue->queue[cursor]);
			}
			for (cursor = 0; cursor < queue->tail; cursor++) {
				printf("%d ", queue->queue[cursor]);
			}
		}
		printf("\n");
	}
	else {
		printf("\nEmpty queue.\n");
	}
}

void testQueue() {
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	initQueue(queue);
	int cursor = 0;
	for (; cursor < 33; cursor++) {
		pushQueue(queue, cursor);
	}
	displayQueue(queue);
	for (cursor = 0; cursor < 33; cursor++) {
		popQueue(queue);
	}
	displayQueue(queue);
	destoryQueue(queue);
	free(queue);
	queue = (struct Queue*)malloc(sizeof(struct Queue));
	initQueue(queue);
	for (cursor = 0; cursor < 15; cursor++) {
		pushQueue(queue, cursor);
	}
	for (cursor = 0; cursor < 10; cursor++) {
		popQueue(queue);
	}
	displayQueue(queue);
	for (cursor = 0; cursor < 60; cursor++) {
		pushQueue(queue, cursor);
	}
	displayQueue(queue);
	for (cursor = 0; cursor < 65; cursor++) {
		popQueue(queue);
	}
	displayQueue(queue);
	destoryQueue(queue);
	free(queue);
}
