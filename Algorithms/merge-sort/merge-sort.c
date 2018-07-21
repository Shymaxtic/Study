#include <stdio.h>
#include <string.h>

void printArray(int* array, int len) {
	printf("\n");
	for(int i = 0; i < len; i++) {
		printf("%d-", array[i]);
	}
	printf("\n");
}

/*
MergeSort(Array, left, right)
If left < right
	1. middle mid = (left + right) / 2
	2. Call MergeSort(Array, left, mid)
	3. Call MergeSort(Array, mid + 1, right)
	4. Call Merge(Array, left, mid, right)
*/

void merge(int* array, int left, int mid, int right) {
	/*
		1. create two temp leftArray[left....mid] and rightArray[mid + 1...right]
		2. divide array into leftArray and rightArray coresponding
		3. compare each element in leftArray and rightArray to merge into array
	*/
	int leftSize = mid - left + 1;
	int rightSize = right - mid;
	int leftArray[leftSize];
	int rightArray[rightSize];
	for(int i = 0; i < leftSize; i++) {
		leftArray[i] = array[left + i]; 
	}
	for(int j = 0; j < rightSize; j++) {
		rightArray[j] = array[mid + 1 + j];
	}
	int i = 0, j = 0, k = left/*You have been wronged here*/; 
	while(i < leftSize && j < rightSize) {
		if(leftArray[i] <= rightArray[j]) {
			array[k] = leftArray[i];
			i++;
		}else {
			array[k] = rightArray[j];
			j++;
		}
		k++;
	}
	while(i < leftSize) {
		array[k] = leftArray[i];
		i++;
		k++;
	}
	while(j < rightSize) {
		array[k] = rightArray[j];
		j++;
		k++;
	}
}

void mergeSort(int* array, unsigned int left, unsigned int right) {
	if(left < right) {
		unsigned int midle = (left + right) / 2;
		mergeSort(array, left, midle);
		mergeSort(array, midle + 1, right);
		merge(array, left, midle, right);
	}
}

void testMergeSort(int* in, int* out, unsigned int len) {
	memcpy(out, in, sizeof(int) * len);
	printf("Before sorting: ");
	printArray(in, len);
	mergeSort(out, 0, len - 1);
	printf("\nAfter sorting: ");
	printArray(out, len);
}
int main() {
	int data[10] = {8, 9, 7, 2, 2, 0, 3, 4, 3, 1};
	int sortedData[10];
	testMergeSort(data, sortedData, 10);
}






