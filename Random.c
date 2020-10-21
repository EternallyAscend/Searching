#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include "Random.h"

int getRandomIntNumber() {
	srand((unsigned)time(NULL));
	return rand();
}

int getRandomIntNumberByRange(int range) {
	srand((unsigned)time(NULL));
	return rand() % range;
}

int* getRandomIntArray(int size) {
	srand((unsigned)time(NULL));
	int item = 0;
	int* intArray = (int*)malloc(sizeof(int) * size);
	for (; item < size; item++) {
		intArray[item] = rand();
	}
	return intArray;
}

int* getRandomIntArrayByRange(int size, int range) {
	srand((unsigned)time(NULL));
	int item = 0;
	int* intArray = (int*)malloc(sizeof(int) * size);
	for (; item < size; item++) {
		intArray[item] = rand() % range;
	}
	return intArray;
}
