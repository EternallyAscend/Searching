//
// Created by MagicBook on 2020/10/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "Layer.h"

//struct Layer {
//    int size;
//    int tail;
//    int* layer;
//};

struct Layer* initLayer() {
    struct Layer* pointer = (struct Layer*)malloc(sizeof(struct Layer));
    pointer->size = 16;
    pointer->tail = 1;
    pointer->layer = (int*)malloc(sizeof(int) * 16);
    pointer->layer[0] = 1;
    pointer->layer[1] = 0;
    return pointer;
}

int isEmptyLayer(struct Layer* layer) {
    if (NULL == layer) {
        return 1;
    }
    if (NULL == layer->layer) {
        free(layer);
        return 1;
    }
    return 0;
}

void extendLayer(struct Layer* layer) {
    if (isEmptyLayer(layer)) {
        return;
    }
    int newSize = layer->size;
    newSize = newSize << 1;
    int* temp = (int*)malloc(sizeof(int) * newSize);
    int cursor = 0;
    for (; cursor < layer->size; cursor++) {
        temp[cursor] = layer->layer[cursor];
    }
    free(layer->layer);
    layer->layer = temp;
    layer->size = newSize;
}

void addLayer(struct Layer* layer, int index) {
    if (isEmptyLayer(layer)) {
        return;
    }
    if (layer->size - 1 == layer->tail) {
        extendLayer(layer);
    }
    layer->layer[++layer->tail] = index;
}

void pushLayer(struct Layer* layer) {
    layer->layer[layer->tail]++;
}

int popLayer(struct Layer* layer) {
    return --layer->layer[layer->tail - 1];
}

int getLayer(struct Layer* layer) {
    if (isEmptyLayer(layer)) {
        return -1;
    }
    return layer->tail;
}

void destroyLayer(struct Layer* layer) {
    if (NULL == layer) {
        return;
    }
    if (NULL != layer->layer) {
        free(layer->layer);
    }
    free(layer);
}

int getLayerPosition(struct Layer* layer, int index) {
    return layer->layer[index];
}
