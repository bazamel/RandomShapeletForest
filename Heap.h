#ifndef HEADER_HEAP
#define HEADER_HEAP

#include <stdlib.h>
#include "TimeSerie.h"

typedef struct Distance *Distance; 
typedef struct Heap* Heap;

Distance getHeapValue(Heap H, int index); //TESTED

int leftSon(int index); //TESTED
int rightSon(int index); //TESTED
int father(int index); //TESTED

Heap createHeap(int size); //TESTED
void destroyHeap(Heap T); //TESTED

void addToHeap(Heap T, Distance distance); //TESTED
void deleteFromHeap(Heap T); //TESTED

void reorganizeUp(Heap T, int s); //TESTED
void reorganizeDown(Heap T, int s); //TESTED

Distance createDistance(double value, TimeSerie instance, TimeSerie shapelet); //TESTED
void destroyDistance(Distance d); //TESTED

double getDistanceValue(Distance distance); //TESTED
int getDistanceLabel(Distance distance); //TESTED
TimeSerie getDistanceInstance(Distance d);

#endif
