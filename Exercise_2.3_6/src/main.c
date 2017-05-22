/*
binary search for insertion sort
*/

#include <stdio.h>
#include <stdlib.h>

#define N 100

int bin_search(int* array, int low, int high, int x) {
	if (low > high) {
		return low;
	}

	int mid = (low + high) / 2;
	if (x < array[mid]) {
		return bin_search(array, low, mid - 1, x);
	}
	else if (x > array[mid]) {
		return bin_search(array, mid + 1, high, x);
	}
	else {
		return mid;
	}
}

void bin_sort(int* array, int n) {
	int i = 0;
	int j = 0;
	int key = 0;
	int idx = 0;

	for (i= 1; i < n; i++) {
		key = array[i];

		j = i - 1;
		idx = bin_search(array, 0, j, key);

		while (j >= idx) {
			array[j + 1] = array[j];
			j--;
		}

		array[idx] = key;
	}

}

void output(int* array, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}

	printf("\n");
}

int main(int argc, char** argv) {
	int vec[N] = {0};
	int n = 0;

	printf("please input the size of sequence:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}

	bin_sort(vec, n);
	output(vec, n);

	return 0;
}