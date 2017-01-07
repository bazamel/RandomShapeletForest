#ifndef HEADER_SPLIT
#define HEADER_SPLIT

#include "DistanceMap.h"
#include <stdlib.h>

typedef struct Split *Split;

Split createSplit(TimeSerie shapelet, double distance, double gain, double gap, DistanceMap distance_map);
double getGain(Split split);
double getGap(Split split);
double getThreshold(Split split);
DistanceMap getSplitDistanceMap(Split s);

#endif