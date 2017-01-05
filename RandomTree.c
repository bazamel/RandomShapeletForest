#include "RandomTree.h"
#include "TimeSerie.h"
#include "Split.h"

struct RandomTree{
    RandomTree leftSon;
    RandomTree rightSon;
    TimeSerie shapelet;
}; 

RandomTree createRandomTree(TimeSerie *time_serie_samples, int l, int u, int r){
	TimeSerieArray shapelet_candidates = malloc(sizeof(*shapelet_candidates) * r);
	for(int i = 0; i<r; i++){
		Shapelet candidate = sampleShapelet(time_serie_samples, l, u);
		addShapelet(shapelet_candidates, candidate);
	}

	Split best_split = bestSplit(time_serie_samples, shapelet_candidates);
	
}

 
