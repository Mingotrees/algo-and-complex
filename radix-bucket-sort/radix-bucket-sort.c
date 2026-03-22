#include <stdio.h>
#define MAX 10
#include <stdbool.h>

typedef struct{
    int data[MAX];
    int count;
}List;

int maxDigits(int max);

int main(){
    List org = {{10,9,2,6,4,1,2,3}, 8};
    int max = maxDigits(802);
    printf("%d", max);
    

    return 0;
}


int maxDigits(int max){
    int e = 1;
    int count = 0;
    while(max > 0){
        count++;
        max/=10;
    }
    return count;
}
