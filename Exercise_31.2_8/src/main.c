#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
	if (b == 0)
		return a;

	return gcd(b, a%b);
}

int lcm(int a, int b){
	int mul = a * b;
	int t = gcd(a, b);

	return mul / t;
}

int main(int argc, char** argv) {
	int n = 0;
	printf("input n:");
	scanf("%d", &n);

	int* vec = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		printf("the %dth value:", i+1);
		scanf("%d", &vec[i]);
	}

	int base = 1;
	for (int i = 0; i < n; i++) {
		base = lcm(vec[i], base);
	}

	printf("the lcm:%d\n", base);

	return 0;
}