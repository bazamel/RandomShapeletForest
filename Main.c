#include "RandomForest.h"

int main(){
	printf("\n");
	printf("\n");
	printf("BEGINNING\n");

	TimeSerieArray dataset = readFromFile("./dataset/synthetic_control.txt"); //300 instances
	RandomForest result = createRandomForest(dataset, 5, 2, 6, 3); //five trees of 3 shapelet candidates between size 1 and 5

	printf("\nENDING");
	printf("\n");
	printf("\n");
	return 0;
}