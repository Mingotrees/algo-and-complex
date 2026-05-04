#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubbleSort(int arr[], int count);
void insertionSort(int arr[], int count);
void selectionSort(int arr[], int count);
void combSort(int arr[], int count);
void shellSort(int arr[], int count);
void gnomeSort(int arr[], int count);
void strandSort(int arr[], int count);
void mergeStrand(int arr1[], int count1, int arr2[], int *count2);
void countingSort(int arr[], int count);
int partitionN(int arr[], int low, int high);


int main(){

}

void bubbleSort(int arr[], int count){
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - i - 1; j++){
            if(arr[j+1] < arr[j]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int count){
    for(int i = 1; i < count; i++){
        int j;
        int value = arr[i]; 
        for(j = i; j > 0 && arr[j-1] < value; j--){
            arr[j-1] = arr[j];
        }
        arr[j] = value;
    }
}

void selectionSort(int arr[], int count){
    for(int i = 0; i < count; i++){
        int smallNdx = i;
        int j;
        for(j = i + 1; j < count; j++){
            if(arr[smallNdx] > arr[j]){
                smallNdx = j;
            }
        }
        if(smallNdx != i){
            int temp = arr[smallNdx];
            arr[smallNdx] = arr[i];
            arr[i] = temp;
        }
    }
}

void combSort(int arr[], int count){
    int gap = count/1.3;
    int isSwapped = 0;
    for(;gap >= 1 || isSwapped; gap /= count/1.3){
        if(gap < 1){
            gap = 1;
        }

        isSwapped = 0;
        for(int i = gap; i < count; i++){
            if(arr[i] < arr[i-gap]){
                isSwapped = 1;
                int temp = arr[i];
                arr[i] = arr[i-gap];
                arr[i-gap] = temp;
            }
        }
    }
}

void shellSort(int arr[], int count){
    int gap = count/2;
    for(;gap >= 1; gap/=2){
        for(int i = gap; i < count; i++){
            int j; int val = arr[i];
            for(int j = i; j >= gap && arr[j-gap] < val; j-=gap){
                arr[j] = arr[j-gap];
            }
            arr[j] = val;
        }
    }
}

void gnomeSort(int arr[], int count){
    int i;
    for(i = 0; i < count;){
        if(i == 0 || arr[i] >= arr[i-1]){
            i++;
        }else{
            int temp = arr[i];
            arr[i] = arr[i-1];
            arr[i-1] = temp;
            i--;
        }
    }
}

void strandSort(int arr[], int count){
    //strand
    int arr1[10] = {0};
    int count1 = 0;
    int k = 0;

    //output
    int arr2[10] = {0};
    int count2 = 0;
    while(count > 0){
        count1 = 0;
        k = 0;
        int i;
        for(i = 0; i < count; i++){
            if(count1 == 0 || arr[i] >= arr1[count1-1]){
                arr1[count1++] = arr[i];
            }else{
                arr[k++] = arr[i];
            }
        }
        mergeStrand(arr1, count1, arr2, &count2);
        count = k;
    }
    memcpy(arr, arr2, sizeof(int)*count2);
}        

void mergeStrand(int arr1[], int count1, int arr2[], int *count2){
    int j, i ,k;
    j = i = k = 0;
    int merge[10];
    while(i < count1 && j < *count2){
        if(arr1[i] < arr2[j]){
            merge[k++] = arr1[i++];
        }else{
            merge[k++] = arr2[j++];
        }
    }

    while(i < count1) merge[k++] = arr1[i++];
    while(j < *count2) merge[k++] = arr2[j++];

    memcpy(arr2, merge, sizeof(int)*k);
    *count2 = k;
}

void countingSort(int arr[], int count){
    int outputArr[10];
    int min = arr[0];
    int max = arr[0];
    for(int i = 1; i < count; i++){
        if(arr[i] < min){
            min = arr[i];
        }

        if(arr[i] > max){
            max = arr[i];
        }
    }

    int range = max - min + 1;
    int* countingArr = (int*)calloc(range, sizeof(int));

    for(int i = 0; i < count; i++){
        int index = arr[i] - min;
        countingArr[index] += 1;
    }

    for(int i = 1; i < range; i++){
        countingArr[i] += countingArr[i-1];
    }

    for(int i = count - 1; i >= 0; i--){
        int index = arr[i] - min;
        outputArr[--countingArr[index]] = arr[i];
    }

    memcpy(arr, outputArr, sizeof(int)*count);
    free(countingArr);
}

void quickSortN(int arr[], int low, int high){
    if(low <  high){
        int pi = partitionN(arr, low, high);

        quickSortN(arr, low, pi-1);
        quickSortN(arr, pi+1, high);
    }
}

 int partitionN(int arr[], int low, int high){
    int pivot = arr[high];
    int n = high - low + 1;

    int *temp = (int*)malloc(n*sizeof(int));
    if(temp == NULL){
        return low;
    }

    int idx = 0;

    for(int i = low; i <= high; i++){
        if(arr[i] <= pivot){
            temp[idx++] = arr[i];
        }
    }

    int pivotIndex = low + idx;
    temp[idx++] = pivot;

    for(int i = low; i <= high; i++){
        if(arr[i] > pivot){
            temp[idx++] = arr[i];
        }
    }

    for(int i = 0; i < n; i++){
        arr[low+i] = temp[i];
    }

    free(temp);
    return pivotIndex;
}

int partitionL(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low-1;
    for(int j = low; j <= high - 1; j++){
        if(arr[j] < pivot){
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp  = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

int partitionH(int arr[], int low, int high){
    int pivot = arr[low];
    int i = low -1 , j = high + 1;

    while(1){
        do{
            i++;
        }while(arr[i] < pivot);

        do{
            j--;
        }while(arr[j] > pivot);
    
        if(i >= j){
            return j;
        }

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}