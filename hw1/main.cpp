#include "./hw1_cpp.h"
#include <cstdio>

int main(){
    int a[10] = { 4, 5, 1, 3, 6, 7, 9, 10, 2, 8 };
    int n = 10;
    int k = 4;

    printf("Randomized: ");

    int ans1 = randomized_select(a, n, k);
    printf("%d\n", ans1);
    if(checker(a, n, k, ans1)==true){
        printf("%s","correct");
    }
    else{
        printf("%s","incorrect");
    }

    puts("");
    printf("Deterministic: ");

    int ans2 = deterministic_select(a, n, k);
    printf("%d\n", ans2);
    if(checker(a, n, k, ans2) == true){
        printf("%s","correct");
    }
    else{
        printf("%s","incorrect");
    }
    puts("");
    return 0;
}
