#include "RandomForest.h"
#include "RandomTree.h"
#include "TimeSerie.h"
#include "Heap.h"
#include <time.h>

struct DistanceMap{
    Heap distances;
    int size;
}; 

struct Distance{
    double value;
    Shapelet candidate;
    TimeSerie instance;
}; 

DistanceMap createDistanceMap(int size){
	DistanceMap result = malloc(sizeof(*result));
	result->size = 0;
	result->distances = createHeap(size);
	return result;
}

// the distances shall be sorted after the addition of one isntance
void addDistance(DistanceMap distance_map, Distance distance){
	addToHeap(distance_map->distances, distance);
	distance_map->size++;
}

///////////////////// TODO /////////////////////////////////
Distance computeEarlyAbandonSlidingDistance(TimeSerie instance, Shapelet candidate){

}

double getDistanceValue(Distance distance){
	return distance->value;
}

int getDistanceLabel(Distance distance){
	return getLabel(distance->candidate);
}

Distance getDistance(DistanceMap map){
	Distance result = getHeapValue(map->distances, 1);
	deleteFromHeap(map->distances);
	return result;
}

Distance getDistanceByIndex(DistanceMap map, int index){
	return getHeapValue(map->distances, index);
}

DistanceMap cloneDistanceMap(DistanceMap distance_map){
	int size = distance_map->size;
	DistanceMap result = createDistanceMap(size);
	Heap target = distance_map->distances;
	for(int i = 0; i<size; i++){
		addToHeap(result->distances, getHeapValue(target, i));
	} 
	return result;
}