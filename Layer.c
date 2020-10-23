#include<stdio.h>
#include<stdlib.h>
#include"Layer.h"

void initLayer(struct Layer* layer) {
	layer->size = 16;
	layer->tail = 1;
	layer->layer = (int*)malloc(sizeof(int) * 16);
	layer->layer[0] = 1;
}

int isEmptyLayer(struct Layer* layer) {
	if (NULL == layer) {
		return 1;
	}
	else if (NULL == layer->layer) {
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
	layer->layer[layer->tail++] = index;
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

int getLayerPosition(struct Layer* layer, int index) {
	if (isEmptyLayer(layer)) {
		return -1;
	}
	return layer->layer[index - 1];
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
