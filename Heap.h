#include "DistanceMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct Heap* Heap;

Distance getHeapValue(Heap H, int index);

int leftSon(int index);

int rightSon(int index);

int father(int index);

Heap createHeap(int size);

void addToHeap(Heap T, Distance distance);

void deleteFromHeap(Heap T);

void destroyHeap(Heap T);

void reorganizeUp(Heap T, int s);

void reorganizeDown(Heap T, int s);
