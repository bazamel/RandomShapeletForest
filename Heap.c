#include "Heap.h"

struct Distance{
    double value;
    Shapelet candidate;
    TimeSerie instance;
}; 

struct Heap{
    Distance *array;
    int size;
};

Distance getHeapValue(Heap H, int index){
    return H->array[index];
}

int leftSon(int index){
    return index*2;
}

int rightSon(int index){
    return index*2+1;
}

int father(int index){
    return index/2;
}

Heap createHeap(int size){
    Heap T = (struct Heap*)malloc(sizeof(*T));
    T->array = malloc(sizeof(Distance)*size);
    T->array[0] = NULL;
    T->size = 1;
    return T;
}

void destroyHeap(Heap T){
    // the inner distances are freed somewhere else
    free(T->array);
    free(T);
}

void addToHeap(Heap T, Distance distance){
    T->array[T->size] = distance;
    reorganizeUp(T,T->size);
    T->size++;
}

void deleteFromHeap(Heap T){
    --T->size;
    T->array[1] = T->array[T->size];
    reorganizeDown(T, 1);
}

void reorganizeUp(Heap T, int s){
    if(s > 1){
        int p = father(s);
        double distance1 = getDistanceValue(getHeapValue(T,p));
        double distance2 = getDistanceValue(getHeapValue(T,s));
        if(distance1 < distance2){
            Distance tmp = T->array[p];
            T->array[p] = T->array[s];
            T->array[s] = tmp;
            reorganizeUp(T, p);
        }
    }
}

void reorganizeDown(Heap T, int s){
    if(s < T->size){
        int o = leftSon(s);
        int p = rightSon(s);
        if(o < T->size){
            if(p < T->size){
                if(getDistanceValue(getHeapValue(T,p)) > getDistanceValue(getHeapValue(T,o))){
                    o=p;
                }
            }
            if(getDistanceValue(getHeapValue(T,o)) > getDistanceValue(getHeapValue(T,s))){
                Distance tmp = T->array[o];
                T->array[o] = T->array[s];
                T->array[s] = tmp;
                reorganizeDown(T,o);
            }
        }
    }
}

Distance createDistance(double value, TimeSerie instance, TimeSerie shapelet){
    Distance result = malloc(sizeof(*result));
    result->value = value;
    result->instance = instance;
    result->candidate = shapelet;
    return result;
}

void destroyDistance(Distance d){
    free(d->instance);
    free(d->candidate);
    free(d);
}

double getDistanceValue(Distance distance){
    return distance->value;
}

int getDistanceLabel(Distance distance){
    return getLabel(distance->candidate);
}

TimeSerie getDistanceInstance(Distance d){
    return d->instance;
}
