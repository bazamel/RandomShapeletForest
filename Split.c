#include "Split.h"

struct Split{
    Shapelet shapelet;
    double distance_threshold;
}; 

Split createSplit(Shapelet shapelet, double distance){
	Split result = malloc(sizeof(*result));
	result->shapelet = shapelet;
	result->distance_threshold = distance;
	return result;
}