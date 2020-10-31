//
// Created by MagicBook on 2020/10/24.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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

struct MinHeap_C* initMinHeap() {
    struct MinHeap_C* pointer = (struct MinHeap_C*)malloc(sizeof(struct MinHeap_C));
    pointer->tail = 0;
    pointer->size = 16;
    pointer->minHeap = (struct Method**)malloc(sizeof(struct Method*) * 16);
    return pointer;
}

void extendMinHeap(struct MinHeap_C* minHeap) {
    if (isEmptyMinHeap(minHeap)) {
        return;
    }
    int newSize = minHeap->size;
    newSize = newSize << 1;
    struct Method** temporary = (struct Method**)malloc(sizeof(struct Mehtod*) * newSize);
    int cursor = 0;
    for (; cursor < minHeap->size; cursor++) {
        temporary[cursor] = minHeap->minHeap[cursor];
    }
    free(minHeap->minHeap);
    minHeap->size = newSize;
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
            int status = compareMethod(minHeap->minHeap[current], minHeap->minHeap[(current - 1) >> 1]);
            if (-65535 == status) {
                return;
            }
            if (-1 == status) {
                struct Method* temporary = minHeap->minHeap[current];
                minHeap->minHeap[current] = minHeap->minHeap[(current - 1) >> 1];
                minHeap->minHeap[(current - 1) >> 1] = temporary;
                current = ((current - 1) >> 1);
            }
            else {
                return;
            }
        }

        if (-1 == compareMethod(minHeap->minHeap[current], minHeap->minHeap[0])) {
            struct Method* temporary = minHeap->minHeap[current];
            minHeap->minHeap[current] = minHeap->minHeap[0];
            minHeap->minHeap[0] = temporary;
        }
    }

}

struct Method* popMinHeap(struct MinHeap_C* minHeap) {
    if (NULL == minHeap) {
        return NULL;
    }
    if (NULL == minHeap->minHeap) {
        return NULL;
    }
    if (0 >= minHeap->tail) {
        return NULL;
    }
    struct Method* result = minHeap->minHeap[0];
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
        struct Method* leftValue = NULL;
        struct Method* rightValue = NULL;
        if ((current << 1) + 1 < minHeap->tail) {
            left = 1;
            leftValue = minHeap->minHeap[(current << 1) + 1];
            if ((current << 1) + 2 < minHeap->tail) {
                right = 1;
                rightValue = minHeap->minHeap[(current << 1) + 2];
            }
        }
        if (1 == left || 1 == right) {
            if (1 == right) {
                if (1 == compareMethod(leftValue, rightValue)) {
                    if (-1 == compareMethod(rightValue, minHeap->minHeap[current])) {
                        struct Method* temporary = minHeap->minHeap[current];
                        minHeap->minHeap[current] = minHeap->minHeap[(current << 1) + 2];
                        minHeap->minHeap[(current << 1) + 2] = temporary;
                        current = (current << 1) + 2;
                    }
                    else {
                        break;
                    }
                }
                else {
                    if (-1 == compareMethod(leftValue, minHeap->minHeap[current])) {
                        struct Method* temporary = minHeap->minHeap[current];
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
                if (-1 == compareMethod(leftValue, minHeap->minHeap[current])) {
                    struct Method* temporary = minHeap->minHeap[current];
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
    return result;

}

void destroyMinHeap(struct MinHeap_C* minHeap) {
    if (NULL == minHeap) {
        return;
    }
    if (NULL == minHeap->minHeap) {
        return;
    }
    free(minHeap->minHeap);
    free(minHeap);
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
        printf("0x%p ", minHeap->minHeap[cursor]);
        printf("%d ", minHeap->minHeap[cursor]->score);
    }
    printf("\n");
}

void testMinHeap() {
    struct MinHeap_C* minHeap = initMinHeap();
    int cursor = 0;
    srand((unsigned)time(NULL));
    for (; cursor < 33; cursor++) {
        struct Method* method = initEmptyMethod();
        method->score = rand() % 10;
        pushMinHeap(minHeap, method);
        displayMinHeap(minHeap);
    }
    printf("Add\n");
    displayMinHeap(minHeap);
    for (; cursor > 0; cursor--) {
        printf("0x%p ", popMinHeap(minHeap));
    }
    destroyMinHeap(minHeap);
    minHeap = initMinHeap();
    for (cursor = 0; cursor < 33; cursor++) {
        pushMinHeap(minHeap, initEmptyMethod());
    }
    displayMinHeap(minHeap);
    for (; cursor > 0; cursor--) {
        printf("0x%p ", popMinHeap(minHeap));
    }
    destroyMinHeap(minHeap);
    printf("\n--");
}

