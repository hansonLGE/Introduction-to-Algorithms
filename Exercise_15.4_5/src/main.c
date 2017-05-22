#include <stdio.h>
#include <stdlib.h>

#define N 100

int lis(int* vec, int* dp, int n) {
	int max = 0;

	for (int i = 0; i < n; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (vec[i] > vec[j] && dp[j] + 1 > dp[i]) {
				dp[i] = dp[j] + 1;
			}
		}

		if (dp[i] > max) {
			printf("%d ", vec[i]);
			max = dp[i];
		}
	}

	printf("\n");

	return max;
}

int main(int argc, char** argv) {
	int vec[N] = {0};
	int n = 0;

	printf("input the size of vec:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}

	int dp[N] = { 0 };
	int len = lis(vec, dp, n);
	printf("length:%d\n", len);

	return 0;
}