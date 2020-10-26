//
// Created by MagicBook on 2020/10/24.
//

#ifndef AI_SEARCHING_QUEUE_C_H
#define AI_SEARCHING_QUEUE_C_H

#include "CheckerBoard.h"

struct Queue_C {
    int head;
    int tail;
    int size;
    struct CheckerBoard** queue;
};

int isEmptyQueue(struct Queue_C* queue);

struct Queue_C* initQueue();

void extendQueue(struct Queue_C* queue);

int pushQueue(struct Queue_C* queue, struct CheckerBoard* value);

struct CheckerBoard* popQueue(struct Queue_C* queue);

void destroyQueue(struct Queue_C* queue);

void displayQueue(struct Queue_C* queue);

void testQueue();

#endif //AI_SEARCHING_QUEUE_C_H
