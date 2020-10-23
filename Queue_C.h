#pragma once
#ifndef QUEUE_C_H
#define QUEUE_C_H

#include "CheckerBoard.h"

struct Queue_C {
	int head;
	int tail;
	int size;
	struct CheckerBoard** queue;
};

int isEmptyQueue(struct Queue_C* queue);

int initQueue(struct Queue_C* queue);

void extendQueue(struct Queue_C* queue);

int pushQueue(struct Queue_C* queue, struct CheckerBoard* value);

struct CheckerBoard* popQueue(struct Queue_C* queue);

void destoryQueue(struct Queue_C* queue);

void displayQueue(struct Queue_C* queue);

void testQueue();

#endif 