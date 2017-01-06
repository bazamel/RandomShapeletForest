typedef struct DistanceMap *DistanceMap; 
typedef struct Distance *Distance; 

DistanceMap createDistanceMap(int size);
void addDistance(DistanceMap distance_map, Distance distance);
Distance computeEarlyAbandonSlidingDistance(TimeSerie instance, Shapelet candidate);