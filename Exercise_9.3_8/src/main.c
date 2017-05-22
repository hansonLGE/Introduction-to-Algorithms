/*
Question: There are 2 sorted arrays A and B of size n each. 
          Write an algorithm to find the median of the array obtained after merging the above 2 arrays(i.e. array of length 2n).
		  The complexity should be O(log(n)).
*/
#include <stdio.h>
#include <stdlib.h>

#define N 100

int get_array_median(int* array, int n) {
	if (n % 2 == 0) {
		return (array[n / 2] + array[n/2 - 1]) / 2;
	}
	else {
		return array[n / 2];
	}
}

int get_median(int* array1, int* array2, int n) {
	int m1 = 0;
	int m2 = 0;

	if (n == 1) {
		return (array1[0] + array2[0]) / 2;
	}
	else if(n == 2){
		return (max(array1[0], array2[0]) + min(array1[1], array2[1])) / 2;
	}
	else {
		m1 = get_array_median(array1, n);
		m2 = get_array_median(array2, n);

		if (m1 < m2) {
			if (n % 2 == 0) {
				return get_median(array1 + n / 2 - 1, array2, n - n / 2 + 1);
			}
			else {
				return get_median(array1 + n / 2, array2, n - n / 2);
			}

		}
		else if (m1 > m2) {
			if (n % 2 == 0) {
				return get_median(array1, array2 + n / 2 - 1, n - n / 2 + 1);
			}
			else {
				return get_median(array1, array2 + n / 2, n - n / 2);
			}
		}
		else {
			return m1;
		}
	}
}

int main(int argc, char** argv) {
	int vec[N] = {0};
	int vec2[N] = { 0 };
	int n = 0;

	printf("please input the size of array:");
	scanf("%d", &n);

	printf("Create the first sorted array:\n");
	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}

	printf("Create the second sorted array:\n");
	for (int j = 0; j < n; j++) {
		printf("input a int data:");
		scanf("%d", &vec2[j]);
	}

	printf("Median is %d\n", get_median(vec, vec2, n));

	return 0;
}