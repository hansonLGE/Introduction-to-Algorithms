/*
binary search for sorted sequence
*/

#define N 100

int bin_search(int* array, int low, int high, int x) {
	if (low > high) {
		return -1;
	}
	
	int mid = (low + high) / 2;
	if (x < array[mid]) {
		return bin_search(array, low, mid - 1, x);
	}
	else if(x > array[mid]){
		return bin_search(array, mid + 1, high, x);
	}
	else {
		return mid;
	}
}

int main(int argc, char** argv) {
	int vec[N] = { 0 };
	int n = 0;
	int x = 0;

	printf("please input the size of sorted sequence:");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("input a int data:");
		scanf("%d", &vec[i]);
	}

	while (1){
		printf("please input a search data:");
		scanf("%d", &x);
		printf("the location is %d\n", bin_search(vec, 0, n - 1, x) + 1);
	}

	return 0;
}