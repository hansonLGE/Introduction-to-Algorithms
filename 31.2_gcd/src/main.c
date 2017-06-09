#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
	if (b == 0)
		return a;

	return gcd(b, a%b);
}
int main(int argc, char** argv) {
	int a = 0;
	int b = 0;

	printf("please input two int:");
	scanf("%d %d", &a, &b);
	printf("the gcd is %d\n", gcd(a, b));
	return 0;
}