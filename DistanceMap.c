

// ////////////
// WARNING : the Heap first value index is 1, not 0 !!!!!!!!!!!
// ////////////

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

void destroyDistanceMap(DistanceMap dm){
	destroyHeap(dm->distances);
	free(dm);
}

// the distances shall be sorted after the addition of one isntance
void addDistance(DistanceMap distance_map, Distance distance){
	addToHeap(distance_map->distances, distance);
	distance_map->size++;
}

Distance computeEarlyAbandonSlidingDistance(TimeSerie instance, Shapelet candidate){
	double min_distance = INFINITY;

	int candidate_size = getTimeSerieSize(candidate);
	int instance_size = getTimeSerieSize(instance);
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
	for(i=1; i<instance_size; i++){
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
	double subsequence_distance = sqrt(min_distance/(double)candidate_size);
	// printf("%lf\n", subsequence_distance);
	return createDistance(subsequence_distance, instance, candidate);
}

double computeEuclideanDistance(double *sequence, double *t, int j, int candidate_size, double mean, double sigma, double min_distance){
	double sum = 0;
	int i;
	for(i = 1; i<candidate_size && sum<min_distance; i++){
		double x = (t[i+j]-mean)/sigma - sequence[i]; //z-normalization
		sum += x*x;
	}
	return sum;
}

int getDistanceMapSize(DistanceMap d){
	return d->size+1;
}

// distance are retrieved by ascending order
Distance getDistance(DistanceMap map){
	Distance result = getHeapValue(map->distances, 1);
	deleteFromHeap(map->distances);
	return result;
}

// distances are retrieved randomly
Distance getDistanceByIndex(DistanceMap map, int index){
	return getHeapValue(map->distances, index);
}

DistanceMap cloneDistanceMap(DistanceMap distance_map){
	int size = getDistanceMapSize(distance_map);
	DistanceMap result = createDistanceMap(size);
	int i;
	for(i = 1; i<size; i++){
		addDistance(result, getDistanceByIndex(distance_map, i));
	} 
	return result;
}

void testDistanceMap(){
	DistanceMap dm = createDistanceMap(10);
	double value1 = 12.5;
	double value2 = 45.9;
	double vector[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	double vector2[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	TimeSerie ts = createTimeSerie(vector, 1, 10);
	TimeSerie ts2 = createTimeSerie(vector2, 2, 10);
	TimeSerie ts3 = createTimeSerie(vector2, 1, 10);
	Distance d = createDistance(value1, ts, ts2);
	Distance d2 = createDistance(value2, ts, ts3);
	addDistance(dm, d);
	addDistance(dm, d2);
	displayDistanceMap(dm);

	DistanceMap clone = cloneDistanceMap(dm);
	displayDistanceMap(clone);
	printf("%lf, ",getDistanceValue(getDistance(clone)));
	printf("%lf,",getDistanceValue(getDistance(clone)));

	destroyDistanceMap(dm);
	destroyDistanceMap(clone);
}

void displayDistanceMap(DistanceMap d){
	int i;
	printf("\n");
	for(i=1; i<getDistanceMapSize(d); i++){
		Distance current_distance = getDistanceByIndex(d, i);
		printf("%lf, %d\n", getDistanceValue(current_distance), getDistanceLabel(current_distance));
	}
	printf("\n");
}