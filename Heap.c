#include "Heap.h"

struct Heap{
    Distance *array;
    int size;
};

Distance getHeapValue(Heap H, int index){
    return T->tab[index];
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
    Heap T = malloc(sizeof(*T));
    T->array = malloc(sizeof(Distance)*size);
    T->array[0] = NULL;
    T->size = 1;
    return T;
}

void addToHeap(Heap T, Distance distance){
    T->array[T->size] = distance;
    reorganizeUp(T,T->size);
    T->size++;
}

void deleteFromHeap(Heap T){
    --(T->size);
    T->array[1] = T->array[T->size];
    reorganizeDown(T, 1);
}

void destroyHeap(Heap T){
    free(T);
}

void reorganizeUp(Heap T, int s){
    if(s != 1){
        int p = father(s);
        double distance1 = getDistanceValue(getHeapValue(T,p));
        double distance2 = getDistanceValue(getHeapValue(T,s));
        if(distance1 < distance2){
            char tmp = T->array[p];
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
                char tmp = T->array[o];
                T->array[o] = T->array[s];
                T->array[s] = tmp;
                reorganizeDown(T,o);
            }
        }
    }
}
