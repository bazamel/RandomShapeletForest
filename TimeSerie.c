#include "TimeSerie.h"

struct TimeSerie{
    double *values;
    int class_label;
}; 

struct TimeSerieArray{
	TimeSerie *time_series;
	int size;
}

void addTimeSerie(TimeSerieArray array, TimeSerie time_serie){
	array->time_series[array->size++] = time_series;
}

TimeSerie getTimeSerie(TimeSerieArray array, int index){
	return array->time_series[index];
}

TimeSerieArray createTimeSerieArray(int size){
	TimeSerieArray result = malloc(sizeof(*result) * size);
	result->size = 0;
}