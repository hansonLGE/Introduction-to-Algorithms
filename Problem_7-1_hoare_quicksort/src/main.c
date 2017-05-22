#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

int hoare_partition(int* vec, int low, int high) {
	int i = low;
	int j = high;
	int key = 0;

	if (low < high) {
		key = vec[low];

		while (i < j) {
			while (i<j && vec[j] > key) {
				j--;
			}
			if (i<j) {
				vec[i] = vec[j];
				i++;
			}

			while (i < j && vec[i] < key) {
				i++;
			}
			if (i < j) {
				vec[j] = vec[i];
				j--;
			}
		}

		vec[i] = key;
	}

	return i;
}

int randomized_partition(int* vec, int low, int high) {
	int tmp = 0;
	int k = 0;

	srand((unsigned int)time(NULL));
	k = rand() % (high - low + 1) + low;

	tmp = vec[low];
	vec[low] = vec[k];
	vec[k] = tmp;

	return hoare_partition(vec, low, high);
}

void randomized_quicksort(int* vec, int low, int high) {
	int mid = 0;
	if (low < high) {
		mid = randomized_partition(vec, low, high);
		randomized_quicksort(vec, low, mid - 1);
		randomized_quicksort(vec, mid + 1, high);
	}
}

int main(int argc, char** argv) {
	int vec[N] = {0};
	int n = 0;

	printf("input the size of vector:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}

	randomized_quicksort(vec, 0, n - 1);

	for (int i = 0; i < n; i++) {
		printf("%d ", vec[i]);
	}

	printf("\n");
	return 0;
}