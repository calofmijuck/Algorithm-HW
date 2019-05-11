#include "./hw1_cpp.h"
#include <iostream>
#include <chrono>
using namespace std::chrono;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int* arr = (int*) malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i) scanf("%d", arr + i);
    auto start = high_resolution_clock::now();
    int ans1 = randomized_select(arr, n, k);
    auto stop = high_resolution_clock::now();
    printf("Randomized: %d, ", ans1);
    if(checker(arr, n, k, ans1)){
        printf("%s","correct");
    }
    else{
        printf("%s","incorrect");
    }
    auto duration = duration_cast<microseconds>(stop - start);
    printf(", Execution time ");
    std::cout << duration.count() / 1000.0 << " ms\n";

    start = high_resolution_clock::now();
    int ans2 = deterministic_select(arr, n, k);
    stop = high_resolution_clock::now();
    printf("Deterministic: %d, ", ans2);
    if(checker(arr, n, k, ans2)){
        printf("%s","correct");
    }
    else{
        printf("%s","incorrect");
    }
    duration = duration_cast<microseconds>(stop - start);
    printf(", Execution time ");
    std::cout << duration.count() / 1000.0 << " ms\n";
    free(arr);
    return 0;
}
