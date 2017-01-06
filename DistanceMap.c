#include "RandomForest.h"
#include "RandomTree.h"
#include "TimeSerie.h"
#include <time.h>

struct DistanceMap{
    Distance *distances;
    int size;
}; 

struct Distance{
    double value;
    Shapelet candidate;
    TimeSerie instance;
}; 

