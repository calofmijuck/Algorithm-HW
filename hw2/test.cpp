#include <cstdio>
#include "hw2_cpp.h"

// Tester - for debugging
int main() {
    Tree tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);
    tree.inOrder(tree.getRoot());
}
