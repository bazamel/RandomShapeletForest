#ifndef HEADER_HEAP
#define HEADER_HEAP

#include <stdlib.h>
#include "TimeSerie.h"

typedef struct Distance *Distance; 
typedef struct Heap* Heap;

Distance getHeapValue(Heap H, int index);

int leftSon(int index);
int rightSon(int index);
int father(int index);

Heap createHeap(int size);
void destroyHeap(Heap T);

void addToHeap(Heap T, Distance distance);
void deleteFromHeap(Heap T);

void reorganizeUp(Heap T, int s);
void reorganizeDown(Heap T, int s);

Distance createDistance(double value, TimeSerie instance, TimeSerie shapelet);
double getDistanceValue(Distance distance);
int getDistanceLabel(Distance distance);
TimeSerie getDistanceInstance(Distance d);

#endif
