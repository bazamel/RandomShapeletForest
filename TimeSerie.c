#include "TimeSerie.h"
#define MAX_LINES 1000

struct TimeSerie{
    double *values;
    int class_label;
}; 

struct TimeSerieArray{
	TimeSerie *time_series;
	int size;
};

void addTimeSerie(TimeSerieArray array, TimeSerie time_serie){
	array->time_series[array->size++] = time_serie;
}

TimeSerie getTimeSerie(TimeSerieArray array, int index){
	return array->time_series[index];
}

TimeSerieArray createTimeSerieArray(int size){
	TimeSerieArray result = malloc(sizeof(*result) * size);
	result->size = 0;
}

TimeSerieArray readFromFile(char *file){
	FILE * current_file = fopen(file, "r");
	char *current_char = malloc(sizeof(char)*MAX_LINES);
	TimeSerieArray result = createTimeSerieArray(MAX_LINES);
	int isLabel = 1;
	while(fgets(current_char, MAX_LINES, current_file)){
		char *value = malloc(sizeof(char)*MAX_LINES);
		double *time_serie = malloc(sizeof(double)*MAX_LINES);
		int j=0, k=0;
		int label;
		int i;
		for(i=0; current_char[i]; i++){
			if(current_char[i] == '\n'){
				if(isLabel){
					label = atoi(value);
					isLabel = 0;
				}else{
					time_serie[k++] = strtod(value, NULL);
				}
				j=0;
			}else{
				value[j++] = current_char[i];
			}
		}
		addTimeSerie(result, createTimeSerie(time_serie, label, k));
		free(time_serie);
		free(value);
	}
	free(current_char);
	fclose(current_file);

	return result;
}

TimeSerie createTimeSerie(double *values, int label, int size){
	TimeSerie result = malloc(sizeof(*result)*size);
	result->class_label = label;
	result->values = malloc(sizeof(double)*size);
	int i;
	for(i=0; i<size; i++){
		result->values[i]=values[i];
	}
	return result;
}

int getLabel(TimeSerie s){
	return s->class_label;
}

double *getSequence(TimeSerie s){
	return s->values;
}

int getTimeSerieArraySize(TimeSerieArray t){
	return t->size;
}