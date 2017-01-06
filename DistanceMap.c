#include "RandomForest.h"
#include "RandomTree.h"
#include "TimeSerie.h"
#include <time.h>

struct DistanceMap{
    Distance *distances;
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
	result->distances = malloc(sizeof(Distance)*size);
	return result;
}

// the distances shall be sorted after the addition of one isntance
void addDistance(DistanceMap distance_map, Distance distance){
	distance_map->distances[distance_map->size++] = distance;
}

Distance computeEarlyAbandonSlidingDistance(TimeSerie instance, Shapelet candidate){

}