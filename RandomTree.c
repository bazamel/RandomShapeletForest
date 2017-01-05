#include "RandomTree.h"
#include "TimeSerie.h"
#include "Split.h"

struct RandomTree{
    RandomTree left_son;
    RandomTree right_son;
    Split split;
    int label;
}; 

// DONE
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
	if(left_son->size == 0 || right_son->size == 0){
		tree->left_son = NULL;
		tree->right_son = NULL;
		tree->label = mostProbableLabel(time_serie_samples);
	}else{
		tree->left_son = createRandomTree(left_son, l, u, r);
		tree->right_son = createRandomTree(right_son, l, u, r);
	}

	return tree;
}

// DONE
Shapelet sampleShapelet(TimeSerieArray time_serie_samples, int l, int u){
	int random_time_serie_index = randomUniformIndex(0, time_serie_samples->size);
	TimeSerie time_serie = time_serie_samples->time_series[random_time_serie_index];
	int time_serie_size = sizeof(time_serie->values)/sizeof(double);
	int candidate_size = randomUniformIndex(l, u);
	int start_position = randomUniformIndex(0, time_serie_size);
	return createTimeSerie(time_serie[start_position], time_serie->class_label, candidate_size);
}

///////////////////// TODO /////////////////////////////////
Split bestSplit(TimeSerieArray time_serie_samples, TimeSerieArray shapelet_candidates){

}

///////////////////// TODO /////////////////////////////////
void distribute(Split split, TimeSerieArray left, TimeSerieArray right){

}

// DONE
int randomUniformIndex(int min, int max){
	return min + rand() / (RAND_MAX / (max - min) + 1);
}

// DONE
int mostProbableLabel(TimeSerieArray array){
// find the most probable label in the dataset
	int result_label;
	int counter_size = 10;
	int *counter = malloc(sizeof(int)*counter_size);
	//count the occurence of labels for each time serie
	for(int i = 0; i<array->size; i++){
		int current_label = getTimeSerie(array, i)->class_label;
		if(current_label >= counter_size){
			realloc(counter, sizeof(int)*(current_label+1));
		}
		counter[current_label]++;
	}
	result_label = maxInt(counter, number_of_labels);
	//return the most frequent one
	return result_label;
}

// DONE
int maxInt(int *array, int size){
// return the most frequent value in the array
	int max = 0;
	int max_index;
	for(int i=0; i<size; i++){
		int current_value = array[i];
		if(max<current_value){
			max = current_value;
			max_index = i;
		}
	}
	return max_index;
}

 
