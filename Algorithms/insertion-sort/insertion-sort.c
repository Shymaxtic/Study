#include <stdio.h>
#include <string.h>

void insertion_sort(int* in, int* out, int len){
	memcpy(out, in, sizeof(int) * len);
	for(int j = 1; j < len; ++j) {
		int i = j - 1;
		int key = out[j];
		while(out[i] > key && i >=0) {
			out[i+1] = out[i];
			i--;
		}
		out[i+1] = key;
	}
}

void test_insertion_sort(int* in, int* out, int len) {
	printf("Before sorting: ");
	for(int i = 0; i < len; ++i) {
		printf("%d - ", in[i]);
	}
	printf("\n");
	insertion_sort(in, out, len);
	printf("After sorting: ");
	for(int i = 0; i < len; ++i) {
		printf("%d - ", out[i]);
	}
	printf("\n");
}
int main() {
	int data[10] = {8, 9, 2, 3, 6, 7, 4, 2, 0, 3};
	int sorted_data[10];
	test_insertion_sort(data, sorted_data, 10);
}