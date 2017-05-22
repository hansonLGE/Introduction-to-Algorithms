#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

int patrition(int* vec, int low, int high) {
	int key = 0;
	int i = 0;
	int j = 0;

	if (low < high) {
		key = vec[low];
		i = low;
		j = high;

		while (i < j) {
			while (i<j && vec[j]>key) {
				j--;
			}
			if (i < j) {
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

	tmp = vec[k];
	vec[k] = vec[low];
	vec[low] = tmp;

	return patrition(vec, low, high);
}

int randomized_select(int* vec, int low, int high, int i) {
	if (low == high) {
		return vec[low];
	}

	int mid = randomized_partition(vec, low, high);
	int k = mid - low + 1;
	if (i == k) {
		return vec[mid];
	}
	else if (i < k) {
		return randomized_select(vec, low, mid - 1, i);
	}
	else {
		return randomized_select(vec, mid + 1, high, i - k);
	}
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
	int idx = 0;

	printf("input the size of a vector:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}

	while(1){
		printf("input the i of the ith smallest element:");
		scanf("%d", &idx);

		printf("the value of the ith smallest element in the vector is:%d\n", randomized_select(vec, 0, n - 1, idx));
	}
	
	return 0;
}