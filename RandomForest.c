#include "RandomForest.h"

struct RandomForest{
    RandomTree *trees;
    int size;
}; 

// D contains the time series from the datasets and the corresponding class labels
RandomForest createRandomForest(TimeSerieArray D, int t, int l, int u, int r){
	RandomForest random_forest = malloc(sizeof(*random_forest));
	random_forest->size = 0;
	random_forest->trees = malloc(sizeof(RandomTree) * t);

	srand(time(NULL)); //needed in sampleTimeSerie
	while(random_forest->size < t){
		int dataset_size = getTimeSerieArraySize(D);
		TimeSerieArray time_serie_samples = sampleTimeSerie(D, dataset_size); //contains samples and associated class labels
		RandomTree random_tree = createRandomTree(time_serie_samples, l, u, r);
		// addTree(random_forest, random_tree);
		random_forest->size++;
	}
	return random_forest;
}

TimeSerieArray sampleTimeSerie(TimeSerieArray D, int size){
	TimeSerieArray samples = createTimeSerieArray(size);
	int random_index;
	int i;
	for(i=0; i<size; i++){
		random_index = randomUniformIndex(0, size);
		TimeSerie selected = getTimeSerie(D, random_index);
		addTimeSerie(samples, selected);
	}
	return samples;
} 

void addTree(RandomForest forest, RandomTree tree){
	forest->trees[forest->size++] = tree;
}

