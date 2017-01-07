typedef struct DistanceMap *DistanceMap; 
typedef struct Distance *Distance; 

DistanceMap createDistanceMap(int size);
void addDistance(DistanceMap distance_map, Distance distance);
Distance computeEarlyAbandonSlidingDistance(TimeSerie instance, Shapelet candidate);
double computeEuclideanDistance(double *sequence, double *t, int j, int candidate_size, double mean, double sigma, double min_distance);
double getDistanceValue(Distance distance);
int getDistanceLabel(Distance distance);
TimeSerie getDistanceInstance(Distance d);
int getDistanceMapSize(DistanceMap d);

Distance getDistance(DistanceMap map);
Distance getDistanceByIndex(DistanceMap map, int index);
DistanceMap cloneDistanceMap(DistanceMap distance_map);