typedef struct DistanceMap *DistanceMap; 
typedef struct Distance *Distance; 

DistanceMap createDistanceMap(int size);
void addDistance(DistanceMap distance_map, Distance distance);
Distance computeEarlyAbandonSlidingDistance(TimeSerie instance, Shapelet candidate);
double getDistanceValue(Distance distance);
int getDistanceLabel(Distance distance);
Distance getDistance(DistanceMap map);
Distance getDistanceByIndex(DistanceMap map, int index);
DistanceMap cloneDistanceMap(DistanceMap distance_map);