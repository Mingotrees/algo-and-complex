#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int fib(int x);
//memoization
int fibUtil(int dp[], int x);

int main(){
    for(int i = 0; i < 10; i++){
        printf("%d ", fib(i));
    }
}

int fib(int x){
    int dp[x+1];
    for(int i = 0; i < x + 1; i++){
        dp[i] = -1;
    }

    return fibUtil(dp, x);
}

int fibUtil(int dp[], int x){
    if(x <= 1){
        return x;
    }

    if(dp[x] != -1){
        return dp[x];
    }

    dp[x] = fibUtil(dp, x-1) + fibUtil(dp, x-2);

    return dp[x];
}