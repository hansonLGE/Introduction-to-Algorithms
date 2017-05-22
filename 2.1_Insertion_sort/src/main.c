#include <stdio.h>
#include <stdlib.h>

#define N 100

void insertion_sort(int* vec, int n) {
	int key = 0;
	int j = 0;

	for (int i = 1; i < n; i++) {
		key = vec[i];

		j = i - 1;
		while (j >= 0 && vec[j] > key) {
			vec[j + 1] = vec[j];
			j--;
		}

		vec[j + 1] = key;
	}
}

void output(int* vec, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", vec[i]);
	}

	printf("\n");
}

int main(int argc, char** argv) {
	int n = 0;
	int vec[N] = {0};

	printf("please input the size of vector:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}

	insertion_sort(vec, n);
	output(vec, n);

	return 0;
}