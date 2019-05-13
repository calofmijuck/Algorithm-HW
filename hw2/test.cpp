#include <cstdio>
#include "hw2_cpp.h"

// Tester - for debugging
int main() {
    Tree tree;
    string str = "";

    freopen("./tests/input", "r", stdin);
    string op;
    int x, t;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cin >> op >> x;
        if(op[0] == 'I') tree.insert(x);
        else if(op[0] == 'D') tree.deleteVal(x);
    }
    tree.printSideways(tree.getRoot(), str);
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cin >> op >> x;
        if(op[0] == 'R') {
            printf("Rank(%d) = %d\n", x, tree.rank(x));
        } else if(op[0] == 'S') {
            printf("Select(%d) = %d\n", x, tree.select(x));
        }
    }
}
