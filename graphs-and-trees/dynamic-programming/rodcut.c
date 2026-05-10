#include <stdio.h>
#include <stdlib.h>

int rodCutN(int[], int);
int rodCutM(int[], int);
int rodCutMUtil(int[], int, int[]);
int rodCutT(int[], int);

int main(){
    struct TestCase {
        const int *price;
        int n;
        int expected;
    } tests[] = {
        {(int[]){0, 1, 5, 8, 9, 10, 17, 17, 20}, 8, 22},
        {(int[]){0, 2, 5, 7, 8}, 4, 10},
        {(int[]){0, 1, 5, 8, 9, 10}, 5, 13}
    };

    int total = (int)(sizeof(tests) / sizeof(tests[0]));
    for(int i = 0; i < total; i++){
        int actualN = rodCutN((int *)tests[i].price, tests[i].n);
        int actualM = rodCutM((int *)tests[i].price, tests[i].n);
        int actualT = rodCutT((int *)tests[i].price, tests[i].n);

        printf("Test %d: rod length %d\n", i + 1, tests[i].n);
        printf("  expected: %d\n", tests[i].expected);
        printf("  naive:    %d\n", actualN);
        printf("  memo:     %d\n", actualM);
        printf("  tabulation:     %d\n\n", actualT);
    }

    return 0;
}

int rodCutN(int price[], int x){
    if (x == 0) return 0;

    int best = 0;
    for(int i = 1; i <= x; i++){
        int val = price[i] + rodCutN(price, x-i);
        if(val > best) best = val;
    }

    return best;
}

int rodCutM(int price[], int x){
    if(x == 0) return 0;

    int *memo = (int *)malloc((x + 1) * sizeof(int));
    if(memo == NULL){
        return 0;
    }

    for(int i = 0; i <= x; i++){
        memo[i] = -1;
    }
    memo[0] = 0;

    int result = rodCutMUtil(price, x, memo);
    free(memo);
    return result;
}

int rodCutMUtil(int price[], int x, int memo[]){
    if(x == 0) return 0;
    if(memo[x] != -1) return memo[x];

    int best = 0;
    for(int i = 1; i <= x; i++){
        int val = price[i] + rodCutMUtil(price, x-i, memo);
        if(val > best) best = val;
    }
    memo[x] = best;
    return best;
}

int rodCutT(int price[], int x){
    int memo[x+1];
    memo[0] = 0;

    for(int i = 1; i <= x; i++){
        int best = 0;
        for(int j = 1; j <= i; j++){
            int val = price[j] + memo[i - j];
            if(val > best) best = val;
        }
        memo[i] = best;
    }

    return memo[x];
}