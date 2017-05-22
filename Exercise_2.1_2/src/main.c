/*
Rewrite the INSERTION-SORT procedure to sort into noincreasing instead of nondecreasing order
*/

#include <stdio.h>
#include <stdlib.h>

#define N 100

void insert_sort(int* arry, int n) {
	int i = 0;
	int key = 0;
	int j = 0;

	for (i = 1; i < n; i++) {
		key = arry[i];

		j = i - 1;
		while (j >= 0 && arry[j] < key) {
			arry[j + 1] = arry[j];
			j--;
		}

		arry[j + 1] = key;
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

	insert_sort(vec, n);
	output(vec, n);
	return 0;
}