typedef struct RandomForest *RandomForest; 

// D contains the time series from the datasets and the corresponding class labels
RandomForest createRandomForest(TimeSerieArray D, int t, int l, int u, int r);

TimeSerieArray sampleTimeSerie(TimeSerieArray D);

void addTree(RandomForest forest, RandomTree tree);