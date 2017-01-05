#include "RandomTree.h"
#include "TimeSerie.h"
#include "Split.h"

struct RandomTree{
    RandomTree left_son;
    RandomTree right_son;
    Split split;
    // int label;
}; 

RandomTree createRandomTree(TimeSerieArray time_serie_samples, int l, int u, int r){
	RandomTree tree = malloc(sizeof(*tree));
	
	//sample the candidate shapelets
	TimeSerieArray shapelet_candidates = malloc(sizeof(*shapelet_candidates) * r);
	for(int i = 0; i<r; i++){
		Shapelet candidate = sampleShapelet(time_serie_samples, l, u);
		addTimeSerie(shapelet_candidates, candidate);
	}
	
	//find the best split and distribute the time series instances according to it
	tree->split = bestSplit(time_serie_samples, shapelet_candidates);
	TimeSerieArray left_son = createTimeSerieArray(r);
	TimeSerieArray right_son = createTimeSerieArray(r);
	distribute(tree->split, left_son, right_son);
	
	//grow the tree recursively
	if(left_son->size == 0){
		tree->left_son = NULL; //make leaf TODO
	}else{
		tree->left_son = createRandomTree(left_son, l, u, r);
	}

	if(right_son->size == 0){
		tree->right_son = NULL; //make leaf TODO
	}else{
		tree->right_son = createRandomTree(right_son, l, u, r);
	}

	return tree;
}

Shapelet sampleShapelet(TimeSerieArray time_serie_samples, int l, int u){

}

Split bestSplit(TimeSerieArray time_serie_samples, TimeSerieArray shapelet_candidates){

}

void distribute(Split split, TimeSerieArray left, TimeSerieArray right){

}

int randomUniformIndex(int max){
	if (max == RAND_MAX+1) { 
		return rand(); 
	}else{ 
		long limit = (RAND_MAX / max)*max; 
		int r; 
		while (true){
			r = rand();
			if(r < limit) break;
		}
		return r % max; 
	}
}

 
