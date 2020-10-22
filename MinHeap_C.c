#include<stdio.h>
#include<stdlib.h>
#include "MinHeap_C.h"

// MinHeap.

int isEmptyMinHeap(struct MinHeap_C* minHeap) {
	if (NULL == minHeap) {
		return 1;
	}
	if (NULL == minHeap->minHeap) {
		return 1;
	}
	return 0;
}

void initMinHeap(struct MinHeap_C* minHeap) {
	minHeap->size = 16;
	minHeap->tail = 0;
	minHeap->minHeap = (struct Method**)malloc(sizeof(struct Method*) * 16);
}

void extendMinHeap(struct MinHeap_C* minHeap) {
	if (isEmptyMinHeap(minHeap)) {
		return;
	}
	int newSize = minHeap->size;
	newSize = newSize << 1;
	int *temporary = (struct Method**)malloc(sizeof(struct Mehtod*) * newSize);
	int cursor = 0;
	for (; cursor < minHeap->size; cursor++) {
		temporary[cursor] = minHeap->minHeap[cursor];
	}
	minHeap->size = newSize;
	// printf("size: %d\n", minHeap->size);
	free(minHeap->minHeap);
	minHeap->minHeap = temporary;
}

void pushMinHeap(struct MinHeap_C* minHeap, struct Method* value) {
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

struct Method* popMinHeap(struct MinHeap_C* minHeap) {
	if (NULL == minHeap) {
		return -65535;
	}
	if (NULL == minHeap->minHeap) {
		return -65535;
	}
	if (0 >= minHeap->tail) {
		return -65534;
	}
	int result = minHeap->minHeap[0];
	if (1 == minHeap->tail) {
		minHeap->tail = 0;
		return result;
	}
	// Adjust the minHeap.
	minHeap->minHeap[0] = minHeap->minHeap[--minHeap->tail];
	int current = 0;
	while (1) {
		int left = 0;
		int right = 0;
		int leftValue;
		int rightValue;
		if ((current << 1) + 1 < minHeap->tail) {
			left = 1;
			leftValue = minHeap->minHeap[(current << 1) + 1];
			if ((current << 1) + 2 < minHeap->tail) {
				right = 1;
				rightValue = minHeap->minHeap[(current << 1) + 2];
			}
		}
		if (left || right) {
			if (right) {
				if (leftValue > rightValue) {
					if (rightValue < minHeap->minHeap[current]) {
						// printf("Exchange %d and %d.\n", rightValue, minHeap->minHeap[current]);
						int temporary = minHeap->minHeap[current];
						minHeap->minHeap[current] = minHeap->minHeap[(current << 1) + 2];
						minHeap->minHeap[(current << 1) + 2] = temporary;
						current = (current << 1) + 2;
					}
					else {
						break;
					}
				}
				else {
					if (leftValue < minHeap->minHeap[current]) {
						// printf("Exchange %d and %d.\n", leftValue, minHeap->minHeap[current]);
						int temporary = minHeap->minHeap[current];
						minHeap->minHeap[current] = minHeap->minHeap[(current << 1) + 1];
						minHeap->minHeap[(current << 1) + 1] = temporary;
						current = (current << 1) + 1;
					}
					else {
						break;
					}
				}
			}
			else {
				if (leftValue < minHeap->minHeap[current]) {
					// printf("Exchange %d and %d.\n", leftValue, minHeap->minHeap[current]);
					int temporary = minHeap->minHeap[current];
					minHeap->minHeap[current] = minHeap->minHeap[(current << 1) + 1];
					minHeap->minHeap[(current << 1) + 1] = temporary;
				}
				break;
			}
		}
		else {
			break;
		}
	}
	// displayMinHeap(minHeap);
	// printf("Pop: %#X\n", result);
	return result;
}

void destoryMinHeap(struct MinHeap_C* minHeap) {
	if (NULL == minHeap) {
		return;
	}
	if (NULL == minHeap->minHeap) {
		return;
	}
	free(minHeap->minHeap);
}

void displayMinHeap(struct MinHeap_C* minHeap) {
	if (isEmptyMinHeap(minHeap)) {
		printf("\nEmpty MinHeap.\n");
		return;
	}
	printf("\nLength: %d\n", minHeap->tail);
	printf("\nLength: %d\n", minHeap->size);
	int cursor = 0;
	for (; cursor < minHeap->tail; cursor++) {
		printf("%#X ", minHeap->minHeap[cursor]);
	}
	printf("\n");
}

void testMinHeap() {
	struct MinHeap_C* minHeap = (struct MinHeap_C*)malloc(sizeof(struct MinHeap_C));
	initMinHeap(minHeap);
	int cursor = 0;
	for (; cursor < 33; cursor++) {
		struct CheckerBoard* checkerBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
		initRandomCheckerBoard(3, 3, checkerBoard);
		pushMinHeap(minHeap, checkerBoard);
	}
	displayMinHeap(minHeap);
	for (; cursor > 0; cursor--) {
		printf("%#X ", popMinHeap(minHeap));
	}
	destoryMinHeap(minHeap);
	free(minHeap);
	minHeap = (struct MinHeap_C*)malloc(sizeof(struct MinHeap_C));
	initMinHeap(minHeap);
	for (cursor = 0; cursor < 33; cursor++) {
		struct CheckerBoard* checkerBoard = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
		initRandomCheckerBoard(3, 3, checkerBoard);
		pushMinHeap(minHeap, checkerBoard);
	}
	displayMinHeap(minHeap);
	for (; cursor > 0; cursor--) {
		printf("%#X ", popMinHeap(minHeap));
	}
	destoryMinHeap(minHeap);
	free(minHeap);
	printf("\n--");
}
