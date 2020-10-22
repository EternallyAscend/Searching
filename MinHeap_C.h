#pragma once
#pragma once
#ifndef MINHEAP_C_H
#define MINHEAP_C_H
#include "CheckerBoard.h"

// MinHeap.

struct MinHeap_C {
	int size;
	int tail;
	struct Method** minHeap;
};

int isEmptyMinHeap(struct MinHeap_C* minHeap);

void initMinHeap(struct MinHeap_C* minHeap);

void extendMinHeap(struct MinHeap_C* minHeap);

void pushMinHeap(struct MinHeap_C* minHeap, struct Method* value);

struct Method* popMinHeap(struct MinHeap_C* minHeap);

void destoryMinHeap(struct MinHeap_C* minHeap);

void displayMinHeap(struct MinHeap_C* minHeap);

void testMinHeap();

#endif