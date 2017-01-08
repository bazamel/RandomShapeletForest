#ifndef HEADER_DISTANCE_MAP
#define HEADER_DISTANCE_MAP

#include "Heap.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct DistanceMap *DistanceMap; 

DistanceMap createDistanceMap(int size); //TESTED
void destroyDistanceMap(DistanceMap dm); //TESTED

void addDistance(DistanceMap distance_map, Distance distance); //TESTED
Distance computeEarlyAbandonSlidingDistance(TimeSerie instance, Shapelet candidate);
double computeEuclideanDistance(double *sequence, double *t, int j, int candidate_size, double mean, double sigma, double min_distance);
int getDistanceMapSize(DistanceMap d); //TESTED

Distance getDistance(DistanceMap map); //TESTED
Distance getDistanceByIndex(DistanceMap map, int index); //TESTED
DistanceMap cloneDistanceMap(DistanceMap distance_map); //TESTED

void testDistanceMap();
void displayDistanceMap(DistanceMap d);

#endif