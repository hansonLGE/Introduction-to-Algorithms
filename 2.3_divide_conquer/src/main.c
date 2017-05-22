/*
A sequence is sorted by the method of divide_conquer.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

void merge(int* vec, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	int i, j, k;

	int *vec_l = (int *)malloc(sizeof(int) * (n1));
	int *vec_r = (int *)malloc(sizeof(int) * (n2));
	memset(vec_l, 0, sizeof(int) * (n1));
	memset(vec_r, 0, sizeof(int) * (n2));

	for (i = 0; i < n1; i++) {
		vec_l[i] = vec[p + i];
	}
	for (j = 0; j < n2; j++) {
		vec_r[j] = vec[q + 1 + j];
	}

	i = 0;
	j = 0;
	k = p;
	while(i<n1 && j<n2) {
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

	while (i < n1) {
		vec[k] = vec_l[i];
		i++;
		k++;
	}

	while (j < n2) {
		vec[k] = vec_r[j];
		j++;
		k++;
	}

	free(vec_l);
	free(vec_r);
}

void merge_sort(int* vec, int p, int r){
	int q = 0;

	if (p < r) {
		q = (p + r) / 2;

		merge_sort(vec, p, q);
		merge_sort(vec, q + 1, r);
		merge(vec, p, q, r);
	}
}

void output(int* vec, int n) {
	for (int i = 0; i < n; i++){
		printf("%d ", vec[i]);
	}

	printf("\n");
}

int main(int argc, char** argv) {
	int n = 0;
	int vec[N] = {0};

	printf("input the size of vector:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}

	merge_sort(vec, 0, n - 1);
	output(vec, n);

	return 0;
}