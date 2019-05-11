#include "./hw1_cpp.h"
#include <iostream>
#include <chrono>
using namespace std::chrono;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int* arr = (int*) malloc(n * sizeof(int));
    int* cop = (int*) malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i) scanf("%d", arr + i);

    int sum = 0;
    int it = 10000;

    for(int i = 0; i < it; ++i) {
        std::copy(arr, arr + n, cop);
        auto start = high_resolution_clock::now();
        int ans1 = randomized_select(arr, n, k);
        auto stop = high_resolution_clock::now();


        if(checker(arr, n, k, ans1)) {
            // printf("Iteration %d passed with ", i);
            auto duration = duration_cast<microseconds>(stop - start);
            // std::cout << duration.count() / 1000.0 << " ms\n";
            sum += duration.count();
        } else {
            printf("Failed at iteration %d\n", i);
            return 0;
        }
    }
    free(arr);
    free(cop);

    printf("Average: %.6lf ms\n", sum / 1000.0 / it);
    return 0;
}
