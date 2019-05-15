#include <cstdio>
#include "hw2_cpp.h"
#define N 10101
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
        printf("%d. %c %d : ", i + 1, op[0], x);
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
        printf("%d\n", out_seq[i]);
    }
    tree.printSideways(tree.getRoot(), str);
    puts("Checking...");
    if(check(opt_seq, in_seq, out_seq, t)) puts("correct");
    else puts("incorrect");
}
