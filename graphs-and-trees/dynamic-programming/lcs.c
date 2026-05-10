#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define MAX 100
//LONGEST COMMON SUBSEQUENCE

//lcs naive
int lcsN(char[], char[], int, int);

//memoization
int lcsM(char[], char[]);
int lcsMUtil(char[], char[], int, int, int[MAX][MAX]);

//tabulations
int lcsT(char[], char[]);


int main(){
    struct TestCase {
        const char *s1;
        const char *s2;
        int expected;
    } tests[] = {
        {"", "", 0},
        {"ABC", "", 0},
        {"ABC", "DEF", 0},
        {"ABC", "ABC", 3},
        {"AGGTAB", "GXTXAYB", 4},
        {"ABCDGH", "AEDFHR", 3},
        {"ABCBDAB", "BDCAB", 4},
        {"XMJYAUZ", "MZJAWXU", 4}
    };

    int total = (int)(sizeof(tests) / sizeof(tests[0]));
    for(int i = 0; i < total; i++){
        int actual = lcsT((char *)tests[i].s1, (char *)tests[i].s2);
        printf("Test %d: s1=\"%s\", s2=\"%s\"\n", i + 1, tests[i].s1, tests[i].s2);
        printf("  expected: %d\n", tests[i].expected);
        printf("  actual:   %d\n\n", actual);
    }

    return 0;
}

int lcsN(char string1[], char string2[], int i, int j){
    if(string1[i] == '\0' || string2[j] == '\0'){
        return 0;
    }

    if(string1[i] == string2[j]){
        return 1 + lcsN(string1, string2, i+1, j+1); 
    }

    return max(lcsN(string1, string2, i+1, j), lcsN(string1, string2, i, j+1));
}

int lcsM(char string1[], char string2[]){
    int len1 = strlen(string1);
    int len2 = strlen(string2);
    if(len1 == 0 || len2 == 0) return 0;

    int dp[MAX][MAX];
    for(int i = 0; i < len1; i++){
        for(int j = 0; j < len2; j++){
            dp[i][j] = -1;
        }
    }

    return lcsMUtil(string1, string2, 0, 0, dp);
}

int lcsMUtil(char string1[], char string2[], int x, int y, int dp[MAX][MAX]){
    if(string1[x] == '\0' || string2[y] == '\0'){
        return 0;
    }

    if(dp[x][y] != -1){
        return dp[x][y];
    }

    if(string1[x] == string2[y]){
        return dp[x][y] = 1 + lcsMUtil(string1, string2, x+1, y+1, dp); 
    }else{
        return dp[x][y] = max(lcsMUtil(string1, string2, x+1, y, dp), lcsMUtil(string1, string2, x, y+1, dp));
    }
}

int lcsT(char string1[], char string2[]){
    int len1 = strlen(string1);
    int len2 = strlen(string2);

    int dp[len1 + 1][len2 + 1];
    for(int i = 0; i <= len1; i++){
        for(int j = 0; j <= len2; j++){
            if(i == 0 || j == 0){
                dp[i][j] = 0;
            }else if(string1[i - 1] == string2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    return dp[len1][len2];
}