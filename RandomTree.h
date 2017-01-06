typedef struct RandomTree *RandomTree;

RandomTree createRandomTree(TimeSerieArray time_serie_samples, int l, int u, int r);

Shapelet sampleShapelet(TimeSerieArray time_serie_samples, int l, int u);

Split bestSplit(RandomTree tree, TimeSerieArray time_serie_samples, TimeSerieArray shapelet_candidates);

void distribute(Split split, TimeSerieArray whole_array, TimeSerieArray left, TimeSerieArray right, DistanceMap distance_map); 
 
int randomUniformIndex(int min, int max);

int mostProbableLabel(TimeSerieArray array);

int maxInt(int *array, int size);

double gain(DistanceMap distance_map, int split_index);
double gap(DistanceMap distance_map, int split_index);
double entropy(DistanceMap distance_map, int number_of_labels);

double *findBestThreshold(RandomTree tree, DistanceMap distance_map);