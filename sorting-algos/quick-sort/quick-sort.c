#include <stdio.h>

#define MAX 20

typedef struct {
	int arr[MAX];
	int count;
} ArrayList;

static void swap(int *a, int *b);
static int partitionLomuto(int arr[], int low, int high);
static int partitionHoare(int arr[], int low, int high);
static int partitionNaive(int arr[], int low, int high);

static void quickSortLomutoRec(int arr[], int low, int high);
static void quickSortHoareRec(int arr[], int low, int high);
static void quickSortNaiveRec(int arr[], int low, int high);

void quickSortLomuto(ArrayList *list);
void quickSortHoare(ArrayList *list);
void quickSortNaive(ArrayList *list);

static void printList(const ArrayList *list);

int main(void) {
	ArrayList base = {{10, 7, 8, 9, 1, 5, 3, 2, 4, 6}, 10};
	ArrayList lomuto = base;
	ArrayList naive = base;
	ArrayList hoare = base;

	quickSortLomuto(&lomuto);
	quickSortNaive(&naive);
	quickSortHoare(&hoare);

	printf("Lomuto: ");
	printList(&lomuto);

	printf("Naive:  ");
	printList(&naive);

	printf("Hoare:  ");
	printList(&hoare);

	return 0;
}

void quickSortLomuto(ArrayList *list) {
	if (list == NULL || list->count <= 1) {
		return;
	}
	quickSortLomutoRec(list->arr, 0, list->count - 1);
}

void quickSortNaive(ArrayList *list) {
	if (list == NULL || list->count <= 1) {
		return;
	}
	quickSortNaiveRec(list->arr, 0, list->count - 1);
}

void quickSortHoare(ArrayList *list) {
	if (list == NULL || list->count <= 1) {
		return;
	}
	quickSortHoareRec(list->arr, 0, list->count - 1);
}

static void quickSortLomutoRec(int arr[], int low, int high) {
	if (low < high) {
		int p = partitionLomuto(arr, low, high);
		quickSortLomutoRec(arr, low, p - 1);
		quickSortLomutoRec(arr, p + 1, high);
	}
}

static void quickSortNaiveRec(int arr[], int low, int high) {
	if (low < high) {
		int p = partitionNaive(arr, low, high);
		quickSortNaiveRec(arr, low, p - 1);
		quickSortNaiveRec(arr, p + 1, high);
	}
}

static void quickSortHoareRec(int arr[], int low, int high) {
	if (low < high) {
		int p = partitionHoare(arr, low, high);
		quickSortHoareRec(arr, low, p);
		quickSortHoareRec(arr, p + 1, high);
	}
}

static int partitionLomuto(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}

static int partitionHoare(int arr[], int low, int high) {
	int pivot = arr[low];
	int i = low - 1;
	int j = high + 1;

	while (1) {
		do {
			i++;
		} while (arr[i] < pivot);

		do {
			j--;
		} while (arr[j] > pivot);

		if (i >= j) {
			return j;
		}

		swap(&arr[i], &arr[j]);
	}
}

static int partitionNaive(int arr[], int low, int high) {
	int pivot = arr[high];
	int temp[MAX];
	int k = low;

	for (int i = low; i < high; i++) {
		if (arr[i] <= pivot) {
			temp[k++] = arr[i];
		}
	}

	int pivotIndex = k;
	temp[k++] = pivot;

	for (int i = low; i < high; i++) {
		if (arr[i] > pivot) {
			temp[k++] = arr[i];
		}
	}

	for (int i = 0; i < high; i++) {
		arr[low+i] = temp[i];
	}

	return pivotIndex;
}

static void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

static void printList(const ArrayList *list) {
	for (int i = 0; i < list->count; i++) {
		printf("%d ", list->arr[i]);
	}
	printf("\n");
}
