//
// Created by MagicBook on 2020/10/24.
//

#ifndef AI_SEARCHING_LAYER_H
#define AI_SEARCHING_LAYER_H

struct Layer {
    int size;
    int tail;
    int* layer;
};

struct Layer* initLayer();

int isEmptyLayer(struct Layer* layer);

void extendLayer(struct Layer* layer);

void addLayer(struct Layer* layer, int index);

void pushLayer(struct Layer* layer);

int popLayer(struct Layer* layer);

int getLayer(struct Layer* layer);

void destroyLayer(struct Layer* layer);

int getLayerPosition(struct Layer* layer, int index);

#endif //AI_SEARCHING_LAYER_H
