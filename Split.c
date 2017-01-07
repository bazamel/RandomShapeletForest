#include "Split.h"

struct Split{
    Shapelet shapelet;
    double distance_threshold;
    double gain;
    double gap;
    DistanceMap distance_map;
}; 

Split createSplit(TimeSerie shapelet, double distance, double gain, double gap, DistanceMap distance_map){
	Split result = malloc(sizeof(*result));
	result->shapelet = shapelet;
	result->distance_threshold = distance;
	result->gain = gain;
	result->gap = gap;
	result->distance_map = distance_map;
	return result;
}

double getGain(Split split){
	return split->gain;
}

double getGap(Split split){
	return split->gap;
}

double getThreshold(Split split){
	return split->distance_threshold;
}

DistanceMap getSplitDistanceMap(Split s){
	return s->distance_map;
}