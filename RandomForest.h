typedef struct RandomForest *RandomForest; 


RandomForest createRandomForest(TimeSerieArray D, int t, int l, int u, int r);

TimeSerieArray sampleTimeSerie(TimeSerieArray D, int size);

void addTree(RandomForest forest, RandomTree tree);