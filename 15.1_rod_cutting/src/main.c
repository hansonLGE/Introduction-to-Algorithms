#include <stdio.h>
#include <stdlib.h>

#define N 32

int cut_rod(int* vec, int n) {
	int revenue = 0;
	int tmp = 0;

	if (n == 0) {
		return 0;
	}

	for (int i = 1; i <= n; i++) {
		tmp = vec[i-1] + cut_rod(vec, n-i);
		if (tmp > revenue) {
			revenue = tmp;
		}
	}

	return revenue;
}

int memoized_cut_rod_aux(int* vec, int n, int* r, int* s) {
	int revenue = 0;
	int tmp = 0;

	if (r[n - 1] > 0)
		return r[n - 1];

	if (n == 0)
		return 0;

	for (int i = 1; i <= n; i++) {
		tmp = vec[i-1] + memoized_cut_rod_aux(vec, n - i, r, s);
		if (tmp > revenue) {
			revenue = tmp;
			s[n-1] = i;
		}
	}

	r[n - 1] = revenue;
	return revenue;
}

int memoized_cut_rod(int* vec, int n, int* s) {
	int r[N] = {0};

	return memoized_cut_rod_aux(vec, n, r, s);
}

void print_cut_rod_solution(int* s, int n) {
	while (n > 0) {
		printf("%d ", s[n - 1]);
		n = n - s[n - 1];
	}
}

int main(int argc, char** argv) {
	int n = 0;
	int vec[N] = {0};
	int s[N] = {0};

	printf("please input the length of rod:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input the price of length %d:", i+1);
		scanf("%d", &vec[i]);
	}

	printf("the max value is: %d\n", memoized_cut_rod(vec, 7, s));
	printf("the solution is:");
	print_cut_rod_solution(s, 7);
	printf("\n");

	return 0;
}