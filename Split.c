#include "Split.h"

struct Split{
    Shapelet shapelet;
    double distance_threshold;
    double gain;
    double gap;
}; 

Split createSplit(Shapelet shapelet, double distance, double gain, double gap){
	Split result = malloc(sizeof(*result));
	result->shapelet = shapelet;
	result->distance_threshold = distance;
	result->gain = gain;
	result->gap = gap;
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