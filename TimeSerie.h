typedef struct TimeSerie *TimeSerie; 
typedef struct TimeSerie *Shapelet; 
typedef struct TimeSerieArray *TimeSerieArray;

void addTimeSerie(TimeSerieArray array, TimeSerie time_serie);

TimeSerie getTimeSerie(TimeSerieArray array, int index);

TimeSerieArray createTimeSerieArray(int size);

TimeSerie createTimeSerie(double *values, int label, int size);