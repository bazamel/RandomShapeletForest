typedef struct RandomTree *RandomTree;

RandomTree createRandomTree(TimeSerieArray time_serie_samples, int l, int u, int r);

Shapelet sampleShapelet(TimeSerieArray time_serie_samples, int l, int u);

Split bestSplit(TimeSerieArray time_serie_samples, TimeSerieArray shapelet_candidates);

void distribute(Split split, TimeSerieArray left, TimeSerieArray right); 
 
int randomUniformIndex(int max);