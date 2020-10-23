#pragma once
#ifndef HEAP_H
#define HEAP_H

// MinHeap.
struct MinHeap {
	int size;
	int tail;
	int* minHeap;
};

int isEmptyMinHeap(struct MinHeap* minHeap);

void initMinHeap(struct MinHeap* minHeap);

void extendMinHeap(struct MinHeap* minHeap);

void pushMinHeap(struct MinHeap* minHeap, int value);

int popMinHeap(struct MinHeap* minHeap);

void destoryMinHeap(struct MinHeap* minHeap);

void displayMinHeap(struct MinHeap* minHeap);

void testMinHeap();

// MaxHeap.
struct MaxHeap {
	int size;
	int tail;
	int* maxHeap;
};

int isEmptyMaxHeap(struct MaxHeap* maxHeap);

void initMaxHeap(struct MaxHeap* maxHeap);

void extendMaxHeap(struct MaxHeap* maxHeap);

void pushMaxHeap(struct MaxHeap* maxHeap, int value);

int popMaxHeap(struct MaxHeap* maxHeap);

void destoryMaxHeap(struct MaxHeap* maxHeap);

void displayMaxHeap(struct MaxHeap* maxHeap);

void testMaxHeap();

#endif