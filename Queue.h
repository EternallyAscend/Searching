#pragma once
#ifndef QUEUE_H
#define QUEUE_H

struct Queue {
	int head;
	int tail;
	int size;
	int* queue;
};

int isEmptyQueue(struct Queue* queue);

int initQueue(struct Queue* queue);

void extendQueue(struct Queue* queue);

int pushQueue(struct Queue* queue, int value);

int popQueue(struct Queue* queue);

void destoryQueue(struct Queue* queue);

void displayQueue(struct Queue* queue);

void testQueue();

#endif 