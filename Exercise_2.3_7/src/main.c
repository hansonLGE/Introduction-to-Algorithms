/*
Describe a O(nlgn)time algorithm that, given a set S of n intergers and another interger X, determines whether or not 
there exist two elements in S whose sum is exactly x.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

void merge(int* vec, int low, int mid, int high) {
	int n1 = mid - low + 1;
	int n2 = high - mid;

	int* vec_l = (int *)malloc(sizeof(int)*n1);
	int* vec_r = (int *)malloc(sizeof(int)*n2);

	memset(vec_l, 0, sizeof(int)*n1);
	memset(vec_r, 0, sizeof(int)*n2);

	int i, j, k;

	for (i = 0; i < n1; i++){
		vec_l[i] = vec[low + i];
	}

	for (j = 0; j < n2; j++) {
		vec_r[j] = vec[mid + 1 + j];
	}

	i = 0;
	j = 0;
	k = low;
	while (i < n1 && j < n2) {
		if (vec_l[i] <= vec_r[j]) {
			vec[k] = vec_l[i];
			i++;
		}
		else {
			vec[k] = vec_r[j];
			j++;
		}

		k++;
	}

	while (i < n1){
		vec[k] = vec_l[i];
		i++;
		k++;
	}

	while (j < n2){
		vec[k] = vec_r[j];
		j++;
		k++;
	}

	free(vec_l);
	free(vec_r);
}

void merge_sort(int* vec, int low, int high) {
	int mid = 0;

	if (low < high) {
		mid = (low + high) / 2;
		merge_sort(vec, low, mid);
		merge_sort(vec, mid + 1, high);
		merge(vec, low, mid, high);
	}
}

int binary_search(int* vec, int low, int high, int key) {
	int mid = 0;

	if (low > high) {
		return -1;
	}
	else {
		mid = (low + high) / 2;
		if (key > vec[mid]) {
			return binary_search(vec, mid + 1, high, key);
		}
		else if (key < vec[mid]){
			return binary_search(vec, low, mid - 1, key);
		}
		else {
			return mid;
		}
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
	int x = 0;
	int idx = 0;

	printf("input the size of vector:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}
	printf("\nplease input the int value of X:");
	scanf("%d", &x);

	merge_sort(vec, 0, n - 1);
	output(vec, n);
	
	for (int i = 0; i < n; i++){
		idx = binary_search(vec, 0, n - 1, x - vec[i]);
		if (idx>= 0){
			printf("exist! %d + %d = %d\n", vec[i], vec[idx], x);
			break;
		}
	}
	
	return 0;
}