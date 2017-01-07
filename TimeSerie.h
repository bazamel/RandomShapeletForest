#ifndef HEADER_TIMESERIE
#define HEADER_TIMESERIE

#include <stdlib.h>
#include <stdio.h>

typedef struct TimeSerie *TimeSerie; 
typedef struct TimeSerie *Shapelet; 
typedef struct TimeSerieArray *TimeSerieArray;

void addTimeSerie(TimeSerieArray array, TimeSerie time_serie);

TimeSerie getTimeSerie(TimeSerieArray array, int index);

TimeSerieArray createTimeSerieArray(int size);
TimeSerieArray readFromFile(char *file);

TimeSerie createTimeSerie(double *values, int label, int size);

int getLabel(TimeSerie s);

double *getSequence(TimeSerie s);

int getTimeSerieArraySize(TimeSerieArray t);

#endif