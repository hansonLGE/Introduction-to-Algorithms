#include <stdio.h>
#include <stdlib.h>

#define M 100
#define N 100

void lcs_length(char *vec_x, char *vec_y, int m, int n, char b[][N], int c[][N]) {
	int i = 0;
	int j = 0;

	while (i < m + 1) {
		c[i][0] = 0;
		i++;
	}

	while (j < n + 1) {
		c[0][j] = 0;
		j++;
	}

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (vec_x[i] == vec_y[j]) {
				c[i + 1][j + 1] = c[i][j] + 1;
				b[i + 1][j + 1] = '~';
			}
			else {
				if (c[i][j + 1] >= c[i + 1][j]) {
					c[i + 1][j + 1] = c[i][j + 1];
					b[i + 1][j + 1] = '#';
				}
				else {
					c[i + 1][j + 1] = c[i+1][j];
					b[i + 1][j + 1] = '$';
				}
			}
		}
	}
}

void print_lcs(char b[][N], char *vec_x, int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}

	if (b[i][j] == '~') {
		print_lcs(b, vec_x, i - 1, j - 1);
		printf("%c ", vec_x[i-1]);
	}
	else if (b[i][j] == '#') {
		print_lcs(b, vec_x, i - 1, j);
	}
	else {
		print_lcs(b, vec_x, i, j-1);
	}
}

int main(int argc, char** argv) {
	int m = 0;
	int n = 0;
	char vec_x[M] = {'\0'};
	char vec_y[N] = {'\0'};
	char b[M][N] = { {'\0'} };
	int c[M][N] = { { 0 } };

	printf("input the size of vec X:");
	scanf("%d", &m);

	printf("input the size of vec Y:");
	scanf("%d", &n);

	for (int i = 0; i < m; i++) {
		printf("X input a character:");
		scanf(" %c", &vec_x[i]);
	}
	printf("----------------------\n");
	for (int i = 0; i < n; i++) {
		printf("Y input a character:");
		scanf(" %c", &vec_y[i]);
	}

	lcs_length(vec_x, vec_y, m, n, b, c);

	for (int i = 0; i < m + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			printf("%d ", c[i][j]);
		}

		printf("\n");
	}

	printf("\n");

	for (int i = 0; i < m + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			printf("%c ", b[i][j]);
		}

		printf("\n");
	}

	print_lcs(b, vec_x, m, n);
	printf("\n");

	return 0;
}