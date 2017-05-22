#include <stdio.h>
#include <stdlib.h>

#define N 100

int unimodal_search(int* vec, int low, int high) {
	int mid = 0;

	if (low == high) {
		return low;
	}
	else {
		mid = (low + high) / 2;
		if (vec[mid] < vec[mid + 1]) {
			return unimodal_search(vec, mid+1, high);
		}
		else if (vec[mid] > vec[mid + 1]){
			return unimodal_search(vec, low, mid-1);
		}
		else {
			return -1;
		}
	}
}

int main(int argc, char** argv) {
	int vec[N] = { 0 };
	int n = 0;

	printf("please input the size of unimodal sequence:");
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		printf("input a data:");
		scanf("%d", &vec[i]);
	}

	int idx = unimodal_search(vec, 0, n - 1);

	printf("the max point(location:%d, value:%d)\n", idx+1, vec[idx]);
	return 0;
}
