#include <cstdio>
#include "hw2_cpp.h"
#define N 1010
extern Tree tree;
// Tester - for debugging
int opt_seq[N], in_seq[N], out_seq[N];
int main() {
    string str = "";

    freopen("./tests/input", "r", stdin);
    string op;
    int x, t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cin >> op >> x;
        in_seq[i] = x;
        if(op[0] == 'I') {
            opt_seq[i] = 0;
            out_seq[i] = os_insert(x);
        } else if(op[0] == 'D') {
            opt_seq[i] = 1;
            out_seq[i] = os_delete(x);
        } else if(op[0] == 'S') {
            opt_seq[i] = 2;
            out_seq[i] = os_select(x);
        } else if(op[0] == 'R') {
            opt_seq[i] = 3;
            out_seq[i] = os_rank(x);
        }
        printf("%c %d : %d\n", op[0], x, out_seq[i]);
        tree.printSideways(tree.getRoot(), str);
    }
    printf("Checking...");
    if(check(opt_seq, in_seq, out_seq, t)) puts("correct");
    else puts("incorrect");
}
