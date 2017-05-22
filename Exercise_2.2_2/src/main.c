/*
selection sort
*/

#include <stdio.h>
#include <stdlib.h>

#define N 100

void selection_sort(int* array, int n) {
	int i = 0;
	int j = 0;
	int tmp = 0;
	int smallest = 0;

	for (i = 0; i < n-1; i++) {
		smallest = i;

		j = i + 1;
		while (j < n) {
			if (array[j] < array[smallest]) {
				smallest = j;
			}
			j++;
		}

		if (smallest != j) {
			tmp = array[smallest];
			array[smallest] = array[i];
			array[i] = tmp;
		}
	}
}

void output(int* arry, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arry[i]);
	}
	printf("\n");
}

int main(int argc, char** argv) {
	int vec[N] = {0};
	int n = 0;

	printf("please input the size of vector:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}

	selection_sort(vec, n);
	output(vec, n);

	return 0;
}