typedef struct RandomForest *RandomForest; 

// D contains the time series from the datasets and the corresponding class labels
RandomForest createRandomForest(TimeSerie *D, int t, int l, int u, int r);
TimeSerie *sampleTimeSerie(TimeSerie *D);
void addTree(RandomForest forest, RandomTree tree);