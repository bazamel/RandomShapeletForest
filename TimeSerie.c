#include "TimeSerie.h"
#define MAX_LINES 1000

struct TimeSerie{
    double *values;
    int class_label;
    int size;
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
	TimeSerieArray result = malloc(sizeof(*result));
	result->time_series = malloc(sizeof(TimeSerie)*size);
	result->size = 0;
}

// improvement : use fgetc instead of fgets
TimeSerieArray readFromFile(char *file){
	FILE * current_file = fopen(file, "r");
	char *current_char = malloc(sizeof(char)*MAX_LINES);
	TimeSerieArray result = createTimeSerieArray(MAX_LINES);
	while(fgets(current_char, MAX_LINES, current_file)){
		char *value = malloc(sizeof(char)*MAX_LINES);
		double *time_serie = malloc(sizeof(double)*MAX_LINES);
		int j=0, k=0;
		int label = -1;
		int i = 2;
		while(1){
			if(current_char[i] == ' ' || current_char[i] == '\n'){
				time_serie[k++] = strtod(value, NULL);
				j=0;
				free(value);
				if(current_char[i]=='\n'){
					break;
				}
				value = malloc(sizeof(char)*MAX_LINES);
				if(current_char[i+1] != '-'){
					++i;
				}
			}else{
				value[j++] = current_char[i];
			}
			++i;
		}
		addTimeSerie(result, createTimeSerie(time_serie, time_serie[0], k));
		free(time_serie);
	}
	free(current_char);
	fclose(current_file);

	return result;
}

TimeSerie createTimeSerie(double *values, int label, int size){
	TimeSerie result = malloc(sizeof(*result)*size);
	result->class_label = label;
	result->values = malloc(sizeof(double)*size);
	result->size = size;
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

void testTimeSerie(){
	TimeSerieArray t = readFromFile("./dataset/synthetic_control.txt");

	// int size = getTimeSerieArraySize(t);
	// int i;
	// for(i=0; i<size; i++){
	// 	toString(getTimeSerie(t, i));
	// }

	destroyTimeSerieArray(t);
}

void toString(TimeSerie s){
	printf("\n");
	printf("Label :%d\n", getLabel(s));
	int i;
	int size = s->size;
	for(i=1; i<size; i++){
		printf("%lf ", getSequence(s)[i]);
	}
	printf("\n");
}

void destroyTimeSerieArray(TimeSerieArray t){
	int i;
	for(i=0; i<t->size; i++){
		destroyTimeSerie(t->time_series[i]);
	}
	free(t->time_series);
	free(t);
}

void destroyTimeSerie(TimeSerie t){
	free(t->values);
	free(t);
}

