#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

void max_heapify(int* vec, int n, int i) {
	int left = 2 * i;
	int right = 2 * i + 1;
	int largest = 0;
	int tmp = 0;

	if (left <= n && vec[left - 1] > vec[i - 1]){
		largest = left;
	}
	else {
		largest = i;
	}

	if (right <= n && vec[right - 1]>vec[largest - 1]){
		largest = right;
	}

	if (largest != i) {
		tmp = vec[i - 1];
		vec[i - 1] = vec[largest - 1];
		vec[largest - 1] = tmp;

		max_heapify(vec, n, largest);
	}
}

void build_max_heap(int* vec, int n) {
	for (int i = n / 2; i >= 1; i--) {
		max_heapify(vec, n, i);
	}
}

void heapsort(int* vec, int n) {
	int tmp = 0;

	build_max_heap(vec, n);

	for (int i = n - 1; i >= 0; i--) {
		tmp = vec[i];
		vec[i] = vec[0];
		vec[0] = tmp;

		n--;
		max_heapify(vec, n, 1);
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

	heapsort(vec, n);

	printf("the order is:");
	for (int i = 0; i < n; i++) {
		printf("%d ", vec[i]);
	}

	printf("\n");

	return 0;
}