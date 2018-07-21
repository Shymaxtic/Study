#include <stdio.h>
#include <string.h>

void exchange_value(int* a, int* b) {
	if(a != b) {
		*a = *a + *b;
		*b = *a - *b;
		*a = *a - *b;
	}
}
unsigned int partition(int* array, unsigned int begin, unsigned int end) {
	int pivot_value = array[end];
	int i = begin - 1;
	for(int j = begin; j <= end - 1; j++) {
		if(array[j] <= pivot_value) {
			i = i + 1;
			printf("\n%d <> %d\n", array[i], array[j]);
			exchange_value(&array[i], &array[j]);
			printf("%d <> %d\n", array[i], array[j]);
		}
	}
	exchange_value(&array[i+1], &array[end]);
	printf("\nPartition: \n");
	for(int x = begin; x <= end; x++) {
		printf("%d-", array[x]);
	}
	return i + 1;
}
void quick_sort(int* array, unsigned int begin, unsigned end) {
	if(begin < end) {
		unsigned int q = partition(array, begin, end);
		quick_sort(array, begin, q - 1);
		quick_sort(array, q + 1, end);
	}
}
void test_quick_sort(const int* in, int* out, int len) {
	memcpy(out, in, sizeof(int) * len);
	printf("Before sorting: ");
	for(int i = 0; i < len; i++) {
		printf("%d-", in[i]);
	}
	quick_sort(out, 0, len - 1);
	printf("\nAfter sorting: ");
		for(int i = 0; i < len; i++) {
		printf("%d-", out[i]);
	}
}

int main() {
	int data[10] = {8, 9, 7, 2, 2, 0, 3, 4, 3, 1};
	int sorted_data[10];
	test_quick_sort(data, sorted_data, 10);
}







