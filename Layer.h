#pragma once
#ifndef LAYER_H
#define LAYER_H


struct Layer {
	int size;
	int tail;
	int* layer;
};

void initLayer(struct Layer* layer);

int isEmptyLayer(struct Layer* layer);

void addLayer(struct Layer* layer, int index);

void pushLayer(struct Layer* layer);

int popLayer(struct Layer* layer);

int getLayer(struct Layer* layer);

int getLayerPosition(struct Layer* layer, int index);

#endif // !LAYER_H
