#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main(int argc, char** argv) {
	int n = 0;
	printf("the array size:");
	scanf("%d", &n);
	int *vec_a = (int *)malloc(n * sizeof(int));
	int *vec_b = (int *)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		printf("input the value of %dth:", i+1);
		scanf("%d", &vec_a[i]);
	}

	int min = 65536;
	int max = 0;
	for (int i = 0; i < n; i++) {
		if (min > vec_a[i]) {
			min = vec_a[i];
		}

		if (max < vec_a[i]) {
			max = vec_a[i];
		}
	}
	//printf("%d %d", min, max);
	int k = max - min;
	int *vec_c = (int *)malloc((k + 1) * sizeof(int));
	for (int i = 0; i <= k; i++) {
		vec_c[i] = 0;
	}

	int idx = 0;
	for (int i = 0; i < n; i++) {
		idx = vec_a[i] - min;
		vec_c[idx]++;
	}

	for (int i = 1; i <= k; i++) {
		vec_c[i] = vec_c[i] + vec_c[i - 1];
	}

	for (int i = n-1; i >= 0; i--) {
		idx = vec_a[i] - min;
		vec_b[vec_c[idx] - 1] = vec_a[i];
		vec_c[idx]--;
	}

	for (int i = 0; i < n; i++) {
		printf("%d ", vec_b[i]);
	}
	printf("\n");

	return 0;
}