#include <random>
#include <cstdio>

void swap(int arr[], int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int randomized_partition(int arr[], int st, int ed) {
    srand(time(NULL));
    int pIdx = st + rand() % (ed - st + 1);
    swap(arr, ed, pIdx);
    int x = arr[ed]; // pivot element
    int i = st - 1;
    for(int j = st; j < ed; ++j) {
        if(arr[j] <= x)
            swap(arr, ++i, j); // increment i then swap
    }
    swap(arr, ++i, ed);
    return i;
}

int randkth(int arr[], int st, int ed, int k) {
    if(st == ed) return arr[st];
    int pivot = randomized_partition(arr, st, ed); // index of pivot
    int idx = pivot - st + 1; // index of pivot from st
    if(k < idx) return randkth(arr, st, pivot - 1, k);
    else if(k > idx) return randkth(arr, pivot + 1, ed, k - idx);
    else return arr[pivot];
}

// find the "k"th smallest element in array "a" with "n" elements by using Randomized-select in CLRS
int randomized_select(int a[], int n, int k) {
    return randkth(a, 0, n - 1, k + 1);
}

int median(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        for(int j = i; j > 0; j--) {
            if(arr[j] < arr[j - 1]) swap(arr, j, j - 1);
            else break;
        }
    }
    return arr[n / 2];
}

int partition(int arr[], int st, int ed, int x) {
    // search for x in arr, and move it to the end
    int i;
    for(i = st; i < ed; ++i) {
        if(arr[i] == x) break;
    }
    swap(arr, i, ed);
    // Partition
    i = st - 1;
    for(int j = st; j < ed; ++j) {
        if(arr[j] <= x) // increment i then swap arr[i] and arr[j]
            swap(arr, ++i, j);

    }
    swap(arr, ++i, ed);
    return i;
}

int detkth(int arr[], int st, int ed, int k) {
    if(st == ed) return arr[st];
    int n = ed - st + 1; // number of elements
    int i;
    int* med = (int*) malloc((n + 4) / 5 * sizeof(int));
    for(i = 0; i < n / 5; ++i)
        med[i] = median(arr + st + 5 * i, 5);
    if(5 * i < n) {
        med[i] = median(arr + st + 5 * i, n % 5);
        i++;
    }
    // choose median of medians
    int medOfMed = (i == 1) ? med[i - 1] : detkth(med, 0, i - 1, i / 2);
    int pivot = partition(arr, st, ed, medOfMed);
    int idx = pivot - st + 1;
    if(idx == k) return arr[pivot];
    else if(idx > k) return detkth(arr, st, pivot - 1, k);
    else return detkth(arr, pivot + 1, ed, k - idx);
}

//find the "k"th smallest element in array "a" with "n" elements by using the worst-case linear-time algorithm in CLRS
int deterministic_select(int a[], int n, int k) {
    return detkth(a, 0, n - 1, k + 1);
}

//check whether the "k"th smallest element in array "a" with "n" elements is the "ans"
bool checker(int a[], int n, int k, int ans){
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(ans > a[i]) cnt++;
    }
    if(cnt == k) return true;
    else return false;
}
