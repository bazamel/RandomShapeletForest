typedef struct Split *Split;

Split createSplit(Shapelet shapelet, double distance, double gain, double gap);
double getGain(Split split);
double getGap(Split split);