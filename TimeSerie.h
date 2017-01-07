#ifndef HEADER_TIMESERIE
#define HEADER_TIMESERIE

#include <stdlib.h>
#include <stdio.h>

typedef struct TimeSerie *TimeSerie; 
typedef struct TimeSerie *Shapelet; 
typedef struct TimeSerieArray *TimeSerieArray;

void addTimeSerie(TimeSerieArray array, TimeSerie time_serie); //TESTED

TimeSerie getTimeSerie(TimeSerieArray array, int index); //TESTED

TimeSerieArray createTimeSerieArray(int size); //TESTED

TimeSerieArray readFromFile(char *file); //TESTED

TimeSerie createTimeSerie(double *values, int label, int size); //TESTED

int getLabel(TimeSerie s); //TESTED

double *getSequence(TimeSerie s); //TESTED

int getTimeSerieArraySize(TimeSerieArray t); //TESTED

void testTimeSerie();

void toString(TimeSerie s); //TESTED

void destroyTimeSerieArray(TimeSerieArray t); //TESTED

void destroyTimeSerie(TimeSerie t); //TESTED

#endif