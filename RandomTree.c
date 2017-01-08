#include "RandomTree.h"

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
	int sample_size = getTimeSerieArraySize(time_serie_samples);
	//sample the candidate shapelets
	TimeSerieArray shapelet_candidates = createTimeSerieArray(r);
	int i;
	for(i = 0; i<r; i++){
		Shapelet candidate = sampleShapelet(time_serie_samples, l, u);
		// toString(candidate);
		addTimeSerie(shapelet_candidates, candidate);
	}
	// OK
	//find the best split and distribute the time series instances according to it
	tree->split = bestSplit(time_serie_samples, shapelet_candidates);
	// printf("%lf, %lf, %lf\n", getGain(tree->split), getGap(tree->split), getThreshold(tree->split));
	TimeSerieArray left_son = createTimeSerieArray(sample_size);
	TimeSerieArray right_son = createTimeSerieArray(sample_size);
	// displayDistanceMap(getSplitDistanceMap(tree->split));
	distribute(tree->split, left_son, right_son); //if no distribution, make leaf (empty arrays)
	// //grow the tree recursively
	int left_size = getTimeSerieArraySize(left_son);
	int right_size = getTimeSerieArraySize(right_son);
	if(left_size == 0 || right_size == 0){
		tree->left_son = NULL;
		tree->right_son = NULL;
		tree->label = mostProbableLabel(time_serie_samples);
		// printf("Label : %d\n", tree->label);
	}else{
		tree->left_son = createRandomTree(left_son, l, u, r);
		tree->right_son = createRandomTree(right_son, l, u, r);
	}

	return tree;
}

// DONE
Shapelet sampleShapelet(TimeSerieArray time_serie_samples, int l, int u){
	int random_time_serie_index = randomUniformIndex(0, getTimeSerieArraySize(time_serie_samples));
	TimeSerie time_serie = getTimeSerie(time_serie_samples, random_time_serie_index);
	int time_serie_size = sizeof(getSequence(time_serie))/sizeof(double);
	int candidate_size = randomUniformIndex(l, u);
	int start_position = randomUniformIndex(0, time_serie_size);
	return createTimeSerie(getSequence(time_serie)+start_position, getLabel(time_serie), candidate_size);
}

// DONE
Split bestSplit(TimeSerieArray time_serie_samples, TimeSerieArray shapelet_candidates){
	int number_of_candidates = getTimeSerieArraySize(shapelet_candidates);
	int sample_size = getTimeSerieArraySize(time_serie_samples);
	Split best_split = createSplit(NULL, -INFINITY, -INFINITY, -INFINITY, NULL);
	// printf("\n%d, %d\n", number_of_candidates, sample_size); //OK
	int i;
	for(i=0; i<number_of_candidates; i++){
		// printf("\nnew candidate evaluation\n");
		Shapelet candidate = getTimeSerie(shapelet_candidates, i);
		DistanceMap current_distance_map = createDistanceMap(sample_size);
		// toString(candidate);
		int j;
		for(j=0; j<sample_size; j++){
			TimeSerie instance = getTimeSerie(time_serie_samples, j);
			Distance current_distance = computeEarlyAbandonSlidingDistance(instance, candidate);
			addDistance(current_distance_map, current_distance);
		}
		// displayDistanceMap(current_distance_map);
		//OK
		//find best threshold
		double *split_components = findBestThreshold(current_distance_map);

		Split current_split = createSplit(candidate, split_components[0], split_components[1], split_components[2], current_distance_map); //parameters : shapelet candidate, best threshold, best gain, best gap, best distance map
		// printf("%lf, %lf, %lf\n", getGain(current_split), getGap(current_split), getThreshold(current_split));
		// //update best threshold
		double current_gain = getGain(current_split);
		double best_gain = getGain(best_split);
		if(current_gain > best_gain || (current_gain == best_gain && getGap(current_split) > getGap(best_split))){
			best_split = current_split;
		}
	}
	// printf("Decision : %lf, %lf, %lf\n", getGain(best_split), getGap(best_split), getThreshold(best_split));
	// displayDistanceMap(getSplitDistanceMap(best_split));
	return best_split;
}

// DONE
void distribute(Split split, TimeSerieArray left, TimeSerieArray right){
	if(getThreshold(split)!=0){
		// printf("\nDistributing\n");
		DistanceMap distance_map = getSplitDistanceMap(split);
		int size = getDistanceMapSize(distance_map);
		int i;
		for(i=1; i<size; i++){
			Distance current_distance = getDistanceByIndex(distance_map, i); 
			TimeSerie instance = getDistanceInstance(current_distance);
			if(getDistanceValue(current_distance) > getThreshold(split)){
				addTimeSerie(right, instance);
			}else{
				addTimeSerie(left, instance);
			}
		}
		// printf("\nDone distributing\n");
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
	int *counter = calloc(counter_size, sizeof(int)*counter_size);
	//count the occurence of labels for each time serie
	int i;
	for(i = 1; i<counter_size; i++){
		int current_label = getLabel(getTimeSerie(array, i));
		counter[current_label]++;
	}
	result_label = maxInt(counter, counter_size);
	//return the most frequent label
	return result_label;
}

// DONE
int maxInt(int *array, int size){
// return the most frequent value in the array
	int max = 0;
	int max_index;
	int i;
	for(i=1; i<size; i++){
		int current_value = array[i];
		if(max<current_value){
			max = current_value;
			max_index = i;
		}
	}
	return max_index;
}

// DONE
double gain(DistanceMap distance_map, double threshold){
	// info gain is the difference between the sum of entropy at the child nodes weighted by the fraction of examples at a particular node, and the entropy at the parent node
	int size = getDistanceMapSize(distance_map); 
	int *right_labels = calloc(size, sizeof(int)*size);
	int *left_labels = calloc(size, sizeof(int)*size);
	// assess number of labels per child
	int i;
	int number_of_labels = 0;
	int left_partition_size = 0;
	// displayDistanceMap(distance_map);
	for(i=1; i<size; i++){
		Distance d = getDistanceByIndex(distance_map, i);
		int current_label = getLabel(getDistanceInstance(d));
		double distance_value = getDistanceValue(d);
		if(left_labels[current_label] == 0 && right_labels[current_label] == 0){
			number_of_labels++;
		}

		// printf("threshold : %lf vs distance : %lf\n", threshold, distance_value);	
		if(distance_value <= threshold){
			left_labels[current_label]++;
			left_partition_size++;
			// printf("left, %d, %d\n", left_labels[current_label], left_partition_size);
		}else{
			right_labels[current_label]++;
			// printf("right, %d, %d\n", right_labels[current_label], size-left_partition_size);
		}
	}
	// printf("number of labels %d\n", number_of_labels);
	// for(i=1; i<number_of_labels+1; i++){
	// 	printf("%d, %d\n", left_labels[i], right_labels[i]);
	// }
	// compute the children entropies : getDistanceByIndex()
	int right_partition_size = size - left_partition_size;
	double left_entropy = entropy(left_labels, number_of_labels)*((double)(left_partition_size)/(double)(size)); //weighted entropy
	double right_entropy = entropy(right_labels, number_of_labels)*((double)(right_partition_size)/(double)(size)); //weighted entropy
	// compute the father entropy : always getDistanceByIndex() instead of getDistance() in this function
	for(i=1; i<number_of_labels+1; i++){
		left_labels[i] += right_labels[i];
	}
	double node_entropy = entropy(left_labels, number_of_labels);
	// return the info gain
	double info_gain = (node_entropy - left_entropy - right_entropy);
	// printf("%lf\n", info_gain);
	free(right_labels);
	free(left_labels);
	return info_gain;
}

// DONE
double gap(DistanceMap distance_map, double threshold){
	// sep gap = sum of right/left subdistances to the candidate divided by the number of right/left instances
	int size = getDistanceMapSize(distance_map);
	int left_size = 0;
	int right_size = 0;
	double left_sum = 0;
	double right_sum = 0;

	int i;
	for(i=1; i<size; i++){
		double current_distance = getDistanceValue(getDistanceByIndex(distance_map, i));
		if(current_distance <= threshold){
			left_size++;
			left_sum += current_distance;
		}else{
			right_size++;
			right_sum += current_distance;
		}
	}
	return (left_sum/(double)(left_size) - right_sum/(double)(right_size));
}

// DONE
double entropy(int *label_counter, int number_of_labels){
	// assess probability of each label (counting) and sum
	double result = 0;
	int total_labels = 0;
	int i;
	for(i=1; i<number_of_labels+1; i++){
		total_labels += label_counter[i];
	}
	for(i=1; i<number_of_labels+1; i++){
		double current_probability;
		if(total_labels != 0 && label_counter[i] != 0){
			current_probability = (double)(label_counter[i])/(double)(total_labels);
			result += current_probability*log2(current_probability);
		}
	}
	// printf("%lf\n", result);
	return result*(-1.0);
}

// DONE
double *findBestThreshold(DistanceMap distance_map){
	double best_threshold = 0;
	// copy distance map
	DistanceMap map = cloneDistanceMap(distance_map);
	int previous_label = -1;
	int previous_distance = 0;
	int size = getDistanceMapSize(map);
	double best_gain = 0;
	double best_gap = 0;

	//evaluate the best threshold from the mid point in terms of information gain and/or separation gap
	int i;
	for(i= 1; i<size; i++){
		// when the class label varies, compute gain
		Distance current_distance = getDistance(map);
		// printf("%lf\n", getDistanceValue(current_distance)); //OK
		double current_threshold;
		if(i>1){
			current_threshold = (getDistanceValue(current_distance)+previous_distance)/2.0; //threshold from the mid points
			int current_label = getLabel(getDistanceInstance(current_distance));
			// if current gain is equal to best gain, compute separation gap and take the max 
			if(previous_label != -1 && previous_label != current_label){
				double current_gain = gain(distance_map, current_threshold);
				double current_gap = gap(distance_map, current_threshold);
				if(current_gain > best_gain ||(current_gain == best_gain && current_gap > best_gap)){
					best_gain = current_gain;
					best_gap = current_gap;
					best_threshold = current_threshold;
				}
			}
			previous_label = current_label;
		}
		previous_distance = getDistanceValue(current_distance);
	}
	// printf("%lf, %lf, %lf\n", best_gain, best_gap, best_threshold);
	double *result = malloc(sizeof(double)*3);
	result[0] = best_threshold;
	result[1] = best_gain;
	result[2] = best_gap;
	return result;
}