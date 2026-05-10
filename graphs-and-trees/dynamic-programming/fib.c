#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//memoization
int fib1(int x);
int fib1Util(int dp[], int x);

//tabulation
int fib2(int x);

//tabulation optimized
int fib3(int x);

int main(){
    for(int i = 0; i < 10; i++){
        printf("%d ", fib1(i));
    }
    printf("\n");
    for(int i = 0; i < 10; i++){
        printf("%d ", fib2(i));
    }
    printf("\n");
    for(int i = 0; i < 10; i++){
        printf("%d ", fib3(i));
    }
}

int fib1(int x){
    int dp[x+1];
    for(int i = 0; i < x + 1; i++){
        dp[i] = -1;
    }

    return fib1Util(dp, x);
}

int fib1Util(int dp[], int x){
    if(x <= 1){
        return x;
    }

    if(dp[x] != -1){
        return dp[x];
    }

    dp[x] = fib1Util(dp, x-1) + fib1Util(dp, x-2);

    return dp[x];
}

int fib2(int x){
    if(x <= 1) return x;

    int dp[x+1];
    dp[0] = 0;
    dp[1] = 1;

    for(int i = 2; i <= x; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[x];
}

int fib3(int x){
    if(x <= 1){
        return x;
    }
    
    int curr, prev = 0, prev1 = 1;
    for(int i = 2; i <= x; i++){
        curr = prev + prev1;
        prev = prev1;
        prev1 = curr;
    }

    return curr;
}