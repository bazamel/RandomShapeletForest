#include "RandomTree.h"
#include "TimeSerie.h"
#include "Split.h"
#include <math.h>

struct RandomTree{
    RandomTree left_son;
    RandomTree right_son;
    RandomTree father;
    Split split;
    int label;
}; 

// DONE
RandomTree createRandomTree(TimeSerieArray time_serie_samples, int l, int u, int r){
	RandomTree tree = malloc(sizeof(*tree));
	
	//sample the candidate shapelets
	TimeSerieArray shapelet_candidates = createTimeSerieArray(r);
	for(int i = 0; i<r; i++){
		Shapelet candidate = sampleShapelet(time_serie_samples, l, u);
		addTimeSerie(shapelet_candidates, candidate);
	}
	
	//find the best split and distribute the time series instances according to it
	tree->split = bestSplit(tree, time_serie_samples, shapelet_candidates);
	TimeSerieArray left_son = createTimeSerieArray(r);
	TimeSerieArray right_son = createTimeSerieArray(r);
	distribute(tree->split, time_serie_samples, left_son, right_son);
	
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
	TimeSerie time_serie = getTimeSerie(time_serie_samples, random_time_serie_index);
	int time_serie_size = sizeof(getSequence(time_serie))/sizeof(double);
	int candidate_size = randomUniformIndex(l, u);
	int start_position = randomUniformIndex(0, time_serie_size);
	return createTimeSerie(time_serie[start_position], getLabel(time_serie), candidate_size);
}

// DONE
Split bestSplit(RandomTree tree, TimeSerieArray time_serie_samples, TimeSerieArray shapelet_candidates){
	int number_of_candidates = getTimeSerieArraySize(shapelet_candidates);
	int sample_size = getTimeSerieArraySize(time_serie_samples);
	Split best_split = createSplit(NULL, 0, 0, 0);
	DistanceMap best_distance_map = createDistanceMap();

	for(int i=0; i<number_of_candidates; i++){
		Shapelet candidate = getTimeSerie(shapelet_candidates, i);
		DistanceMap current_distance_map = createDistanceMap();
		for(int j=0; j<sample_size; j++){
			TimeSerie instance = getTimeSerie(time_serie_samples, j);
			Distance current_distance = computeEarlyAbandonSlidingDistance(instance, candidate);
			addDistance(current_distance_map, current_distance);
		}
		//find best threshold
		double *split_components = findBestThreshold(tree, current_distance_map);
		Split current_split = createSplit(candidate, split_components[0], split_components[1], split_components[2]); //parameters : shapelet candidate, best threshold, best gain, best gap
		//update best threshold
		double current_gain = getGain(current_split);
		double best_gain = getGain(best_split);
		if(current_gain > best_gain || (current_gain == best_gain && getGap(current_split) > getGap(best_split))){
			best_split = current_split;
		}
	}
	return best_split;
}

// DONE
void distribute(Split split, TimeSerieArray left, TimeSerieArray right, DistanceMap distance_map){
	int size = whole_array->size;
	for(int i=0; i<size; i++){
		Distance current_distance = getDistanceByIndex(distance_map, i); 
		TimeSerie instance = getDistanceInstance(current_distance);
		if(getDistanceValue(current_distance) > getThreshold(split)){
			addTimeSerie(right, instance);
		}else{
			addTimeSerie(left, instance);
		}
	}
}

// DONE
int randomUniformIndex(int min, int max){
// return a random uniform number between min and max
	return min + rand() / (RAND_MAX / (max - min) + 1);
}

// DONE
int mostProbableLabel(TimeSerieArray array){
// find the most probable label in the dataset
	int result_label;
	int counter_size = getTimeSerieArraySize(array);
	int *counter = calloc(sizeof(int)*counter_size);
	//count the occurence of labels for each time serie
	for(int i = 0; i<counter_size; i++){
		int current_label = getLabel(getTimeSerie(array, i));
		counter[current_label]++;
	}
	result_label = maxInt(counter, number_of_labels);
	//return the most frequent label
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

// DONE
double gain(DistanceMap distance_map, int split_index){
	// info gain is the difference between the sum of entropy at the child nodes weighted by the fraction of examples at a particular node, and the entropy at the parent node
	int size = getDistanceMapSize(distance_map); 
	double *right_labels = calloc(sizeof(double)*size);
	double *left_labels = calloc(sizeof(double)*size);
	
	// assess number of labels per child
	int i;
	int number_of_labels = 0;
	for(i=0; i<size; i++){
		int current_label = getDistanceLabel(getDistanceByIndex(distance_map, i));
		if(left_labels[current_label] == 0 && right_labels[current_label] == 0){
			number_of_labels++;
		}

		if(i <= split_index){
			left_labels[current_label]++;
		}else{
			right_labels[current_label]++;
		}
	}
	// compute the children entropies : getDistanceByIndex()
	int left_partition_size = split_index+1;
	int right_partition_size = size - left_partition_size;
	double left_entropy = entropy(left_labels, number_of_labels)*(left_partition_size/size); //weighted entropy
	double right_entropy = entropy(right_labels, number_of_labels)*(right_partition_size/size); //weighted entropy
	// compute the father entropy : always getDistanceByIndex() instead of getDistance() in this function
	for(i=0; i<number_of_labels; i++){
		left_labels[i] += right_labels[i];
	}
	double node_entropy = entropy(left_labels, number_of_labels);
	// return the info gain
	return (node_entropy - left_entropy - right_entropy);
}

// DONE
double gap(DistanceMap distance_map, int split_index){
	DistanceMap map = cloneDistanceMap(distance_map);
	// sep gap = sum of right/left subdistances to the candidate divided by the number of right/left instances
	int size = distance_map->size;
	int left_size = 0;
	int right_size = 0;
	double left_sum = 0;
	double right_sum = 0;

	for(int i=0; i<size; i++){
		int current_distance = getDistanceValue(getDistance(map));
		if(i <= split_index){
			left_size++;
			left_sum += current_distance;
		}else{
			right_size++;
			right_sum += current_distance;
		}
	}
	return (left_sum/left_size - right_sum/right_size);
}

// DONE
double entropy(double *label_counter, int number_of_labels){
	// assess probability of each label (counting) and sum
	double result = 0;
	int total_labels = 0;
	int i;
	for(i=0; i<number_of_labels; i++){
		total_labels += label_counter[i];
	}
	for(i=0; i<number_of_labels; i++){
		double current_probability = label_counter[i]/(double)total_labels;
		result += current_probability*log2(current_probability);
	}
	return result*(-1.0);
}

// DONE
double *findBestThreshold(RandomTree tree, DistanceMap distance_map){
	double best_threshold = 0;
	// copy distance map
	DistanceMap map = cloneDistanceMap(distance_map);
	int previous_label = -1;
	int previous_threshold = 0;
	int size = getDistanceMapSize(map);
	double best_gain = 0;
	double best_gap = 0;

	//evaluate the best threshold from the mid point in terms of information gain and/or separation gap
	for(int i= 0; i<size; i++){
		// when the class label varies, compute gain
		Distance current_distance = getDistance(map);
		double current_threshold = (getDistanceValue(current_distance)+previous_threshold)/2.0; //threshold from the mid points
		int current_label = getDistanceLabel(current_distance);
		// if current gain is equal to best gain, compute separation gap and take the max 
		if(previous_label != -1 && previous_label != current_label){
			double current_gain = gain(distance_map, i);
			double current_gap = gap(distance_map, i);
			if(current_gain > best_gain ||(current_gain == best_gain && current_gap > best_gap)){
				best_gain = current_gain;
				best_gap = current_gap;
				best_threshold = current_threshold;
			}
		}
		previous_label = current_label;
		previous_threshold = current_threshold;
	}
	double *result = malloc(sizeof(double)*3);
	result[0] = best_threshold;
	result[1] = best_gain;
	result[2] = best_gap;
	return result;
}