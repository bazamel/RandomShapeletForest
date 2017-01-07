#include "DistanceMap.h"

struct DistanceMap{
    Heap distances;
    int size;
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

Distance computeEarlyAbandonSlidingDistance(TimeSerie instance, Shapelet candidate){
	double min_distance = INFINITY;

	int candidate_size = sizeof(getSequence(candidate))/sizeof(double);
	int instance_size = sizeof(getSequence(instance))/sizeof(double);
	TimeSerie ts1, ts2;
	if(candidate_size<=instance_size){
		ts1 = instance;
		ts2 = candidate;
	}else{
		// else, switch
		ts1 = candidate;
		ts2 = instance;
		int tmp = candidate_size;
		candidate_size = instance_size;
		instance_size = tmp;
	}

	double *t = malloc(sizeof(double)*candidate_size*2);
	double ex1 = 0;
	double ex2 = 0;
	int i;
	for(i=0; i<instance_size; i++){
		double d = getSequence(ts1)[i];
		ex1 += d;
		ex2 += d*d;
		t[i%candidate_size] = d;
		t[(i%candidate_size)+candidate_size] = d;

		if(i>=candidate_size-1){
			int j = (i+1)%candidate_size;
			double mean = ex1/candidate_size;
			double sigma = sqrt(ex2/candidate_size - mean*mean);
			double distance = computeEuclideanDistance(getSequence(ts2), t, j, candidate_size, mean, sigma, min_distance);
			if(distance < min_distance){
				min_distance = distance;
			}
			ex1-=t[j];
			ex2-=t[j]*t[j];
		}
	}

	return createDistance(sqrt(min_distance/candidate_size), instance, candidate);
}

double computeEuclideanDistance(double *sequence, double *t, int j, int candidate_size, double mean, double sigma, double min_distance){
	double sum = 0;
	int i;
	for(i = 0; i<candidate_size && sum<min_distance; i++){
		double x = (t[i+j]-mean)/sigma - sequence[i]; //z-normalization
		sum += x*x;
	}
	return sum;
}

int getDistanceMapSize(DistanceMap d){
	return d->size;
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
	int i;
	for(i = 0; i<size; i++){
		addToHeap(result->distances, getHeapValue(target, i));
	} 
	return result;
}