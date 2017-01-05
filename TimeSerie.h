typedef struct TimeSerie *TimeSerie; 
typedef struct TimeSerie *Shapelet; 
typedef struct TimeSerieArray *TimeSerieArray;

void addShapelet(TimeSerieArray array, TimeSerie time_serie);

TimeSerieArray createTimeSerieArray(int size);