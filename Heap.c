#include<stdio.h>
#include<stdlib.h>
#include "Heap.h"

int isEmptyMinHeap(struct MinHeap* minHeap) {
	if (NULL == minHeap) {
		return 1;
	}
	if (NULL == minHeap->minHeap) {
		return 1;
	}
	return 0;
}

void initMinHeap(struct MinHeap* minHeap) {
	minHeap->size = 16;
	minHeap->tail = 0;
	minHeap->minHeap = (int*)malloc(sizeof(int));
}

void extendMinHeap(struct MinHeap* minHeap) {
	if (isEmptyMaxHeap(minHeap)) {
		return;
	}
	int newSize = minHeap->size;
	newSize = newSize << 1;
	int *temporary = (int*)malloc(sizeof(int) * newSize);
	int cursor = 0;
	for (; cursor < minHeap->size; cursor++) {
		temporary[cursor] = minHeap->minHeap[cursor];
	}
	minHeap->size = newSize;
	free(minHeap->minHeap);
	minHeap->minHeap = temporary;
}

void pushMinHeap(struct MinHeap* minHeap, int value) {
	if (isEmptyMinHeap(minHeap)) {
		return;
	}
	if (minHeap->tail == minHeap->size) {
		extendMinHeap(minHeap);
	}
	minHeap->minHeap[minHeap->tail++] = value;
	// Adjust the minHeap.
	if (1 == minHeap->tail) {
		return;
	}
	else {
		int current = minHeap->tail - 1;
		while ((current - 1) >> 1) {
			if (minHeap->minHeap[current] < minHeap->minHeap[(current - 1) >> 1]) {
				int temporary = minHeap->minHeap[current];
				minHeap->minHeap[current] = minHeap->minHeap[(current - 1) >> 1];
				minHeap->minHeap[(current - 1) >> 1] = temporary;
				current = ((current - 1) >> 1);
			}
			else {
				return;
			}
		}
		if (minHeap->minHeap[current] < minHeap->minHeap[0]) {
			int temporary = minHeap->minHeap[current];
			minHeap->minHeap[current] = minHeap->minHeap[0];
			minHeap->minHeap[0] = temporary;
		}
	}
}

int popMinHeap(struct MinHeap* minHeap) {

}

void destoryMinHeap(struct MinHeap* minHeap) {
	if (NULL != minHeap) {
		if (NULL != minHeap->minHeap) {
			free(minHeap->minHeap);
		}
	}
}

void displayMinHeap(struct MinHeap* minHeap) {
	if (isEmptyMinHeap(minHeap)) {
		return;
	}
	printf("\nLength: %d\n", minHeap->tail);
	printf("\nLength: %d\n", minHeap->size);
	int cursor = 0;
	for (; cursor < minHeap->tail; cursor++) {
		printf("%d ", minHeap->minHeap[cursor]);
	}
	printf("\n");
}

void testMinHeap() {
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
	initMinHeap(minHeap);
	int cursor = 0;
	for (; cursor < 33; cursor++) {
		pushMinHeap(minHeap, 100 - cursor);
	}
	displayMinHeap(minHeap);
	destoryMinHeap(minHeap);
	free(minHeap);
}

// MaxHeap.

int isEmptyMaxHeap(struct MaxHeap* maxHeap) {

}

void initMaxHeap(struct MaxHeap* maxHeap) {

}

void extendMaxHeap(struct MaxHeap* maxHeap) {

}

void pushMaxHeap(struct MaxHeap* maxHeap, int value) {

}

int popMaxHeap(struct MaxHeap* maxHeap) {

}

void destoryMaxHeap(struct MaxHeap* maxHeap) {

}

void displayMaxHeap(struct MaxHeap* maxHeap) {

}

void testMaxHeap() {

}
